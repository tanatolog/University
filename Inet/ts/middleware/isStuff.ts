import http = require("http");
import { checkToken } from "../utils/generateToken";

type UserPayload = {
  id: string;
  login: string;
  email: string;
  admin: boolean;
};

export class MyRequest {
  currentUser?: UserPayload;
  old: http.IncomingMessage;

  constructor(m: http.IncomingMessage) {
    this.old = m;
  }
}

export function isStuff(
  req: MyRequest,
  res: http.ServerResponse,
  cookie: Map<string, any>
) {
  // const cookie = parseCookie(req.headers.cookie);
  // console.log(cookie);
  const token = cookie.get("token");

  if (token===undefined) {
    return false;
  }

  try {
    const payload = checkToken(token) as UserPayload;
    req.currentUser = payload;
    return true;
  } catch (err) {
    res.writeHead(400, { "Content-Type": "application/json" });
    res.end(global.JSON.stringify({ res: false }));
    return false;
  }
}
/*export function isAdmin(
  req: MyRequest,
  res: http.ServerResponse,
) {
  try {
    const d = req.currentUser?.admin;
    if (d === true) return true;
  } catch (e) {
    res.writeHead(400, { "Content-Type": "application/json" });
    res.end(global.JSON.stringify({ res: false }));
    // res.status(400).json({ success: false, message });
    return false;
  }
}*/
