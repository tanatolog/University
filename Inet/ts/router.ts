import type { MyRequest } from "./middleware/isStuff";

export class Route {
  route: Function;
  middlewares: Array<any>;
  constructor(route: Function, middlewares: Array<any>) {
    this.route = route;
    this.middlewares = middlewares;
  }
}
export function route(
  handle: Map<string, Route>,
  pathname: string,
  request: MyRequest,
  response: any,
  postData: Map<string, any>,
  cookie: Map<string, any>
) {
  //console.log(cookie);
  const R = handle.get(pathname);
  var d;
  if (R) {
    R.middlewares.forEach((middleware: any) => {
      d=middleware(request, response, cookie);
    });
    if (d!=false)
    R.route(response, postData, cookie);
  } else {
    response.writeHead(404, { "Content-Type": "text/plain" });
    response.write("404 Not found");
    response.end();
  }
}
