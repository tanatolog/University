import server = require("./app");
import router = require("./router");
import postRequestHandlers = require("./postRequestHandlers");

import prisma from "./prismaBd";
import { isStuff } from "./middleware/isStuff";

const post = new Map<string, any>();
post.set(
  "/registration",
  new router.Route(postRequestHandlers.registration, [])
);
post.set(
  "/autorization",
  new router.Route(postRequestHandlers.autorization, [])
);
post.set("/chat/add", new router.Route(postRequestHandlers.addChat, [isStuff]));
post.set(
  "/group/chat/add",
  new router.Route(postRequestHandlers.addGroupChat, [isStuff])
);
post.set(
  "/add/to/chat",
  new router.Route(postRequestHandlers.addToChat, [isStuff])
);
post.set(
  "/blog/add",
  new router.Route(postRequestHandlers.addArticle, [isStuff])
);
post.set(
  "/blog/edit",
  new router.Route(postRequestHandlers.updateArticle, [isStuff])
);
post.set(
  "/comment/add",
  new router.Route(postRequestHandlers.addComment, [isStuff])
);
post.set("/sub/add", new router.Route(postRequestHandlers.sub, [isStuff]));
post.set("/sub/delete", new router.Route(postRequestHandlers.unsub, [isStuff]));
post.set(
  "/blog/del",
  new router.Route(postRequestHandlers.delBlog, [isStuff])
);
post.set(
  "/user/del",
  new router.Route(postRequestHandlers.delUser, [isStuff])
);

// handle["POST"] = post;

async function main() {
  server.start(router.route, post);
}

main()
  .then(async () => {
    await prisma.$disconnect();
  })
  .catch(async (e) => {
    console.error(e);
    await prisma.$disconnect();
    process.exit(1);
  });
