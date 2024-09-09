import http = require("http");
import WebSocket = require("ws");

import getRequestHandlers = require("./getRequestHandlers");
import { MyRequest } from "./middleware/isStuff";

const HOST = "localhost";
const PORT = 3000;

export function start(route: any, handle: Map<string, any>) {
  const server = http.createServer((req, res) => {
    const cookie = parseCookie(req.headers.cookie);
    const params = getParamsUrl(req.url);

    if (req.method === "GET" && typeof req.url !== "undefined") {
      const path = req.url.split("?")[0];
      switch (path) {
        case "/info/chat": {
          getRequestHandlers.getChatInfo(
            res,
            params.get("cid"),
            cookie.get("uid")
          );
          break;
        }
        case "/chat": {
          getRequestHandlers.getChatAndLast(
            res,
            params.get("cid"),
            cookie.get("uid")
          );
          break;
        }
        case "/chats": {
          getRequestHandlers.getChats(res, cookie.get("uid"));
          break;
        }
        case "/user": {
          getRequestHandlers.getUserData(
            res,
            cookie.get("uid"),
            params.get("id"),
            cookie.get("role")
          );
          break;
        }
        case "/blog": {
          getRequestHandlers.getBlog(
            res,
            params.get("id"),
            cookie.get("uid"),
            cookie.get("role")
          );
          break;
        }
        case "/blog/add": {
          getRequestHandlers.addBlog(res, cookie.get("uid"));
          break;
        }
        case "/blog/edit": {
          getRequestHandlers.updateBlog(
            res,
            params.get("id"),
            cookie.get("uid")
          );
          break;
        }
        case "/blogs": {
          let page = 0;
          if (typeof params.get("page") === "undefined") {
            page = 1;
          } else {
            page = params.get("page");
          }
          getRequestHandlers.getBlogs(res, 20, page, cookie.get("uid"));
          break;
        }
        case "/sub": {
          let page = 0;
          if (typeof params.get("page") === "undefined") {
            page = 1;
          } else {
            page = params.get("page");
          }
          getRequestHandlers.getMySubs(res, 20, page, cookie.get("uid"));
          break;
        }
        default: {
          getRequestHandlers.send404(res);
          break;
        }
      }
    }

    if (req.method === "POST") {
      const body = new Array<any>();
      req.setEncoding("utf8");
      req.addListener("data", (chunk) => {
        body.push(chunk);
      });
      req.addListener("end", () => {
        const json = JSON.parse(body.toString());
        const result: Map<string, any> = new Map(Object.entries(json));
        const myReq = new MyRequest(req);
        // console.log(req.headers);
        route(handle, req.url, myReq, res, result, cookie);
      });
    }
  });

  server.listen(PORT, () => {
    console.log(`listening port ${PORT}`);
  });

  const ws = new WebSocket.Server({ server });
  ws.on("connection", function (wss, request) {
    const cookie = parseCookie(request.headers.cookie);
    const url = getParamsUrl(request.url);
    getRequestHandlers.checkAndAddChat(
      wss,
      url.get("chat"),
      cookie.get("uid"),
      cookie.get("name")
    );
    wss.on("close", function close() {
      getRequestHandlers.removeFromChat(wss);
    });
    wss.on("message", function incoming(data) {
      getRequestHandlers.sendMessage(wss, data);
    });
  });
}

export function parseCookie(cookie: any): Map<string, any> {
  let match;
  const search = /([^&= ]+)=?([^;]+);?/g;
  const urlParams = new Map<string, any>();

  match = search.exec(cookie);
  while (match != null) {
    urlParams.set(match[1], match[2]);
    match = search.exec(cookie);
  }
  return urlParams;
}

function decode(s: any) {
  const pl = /\+/g;
  return decodeURIComponent(s.replace(pl, " "));
}

function getParamsUrl(url: any): Map<string, any> {
  let match;
  const search = /([^&=]+)=?([^&]*)/g;
  // eslint-disable-next-line func-style
  let query = url.split("/").pop();
  const pos = query.indexOf("?") + 1;
  const urlParams = new Map<string, any>();
  if (pos < 1) return urlParams;

  query = query.substring(pos);
  match = search.exec(query);
  while (match != null) {
    urlParams.set(decode(match[1]), decode(match[2]));
    match = search.exec(query);
  }

  return urlParams;
}
