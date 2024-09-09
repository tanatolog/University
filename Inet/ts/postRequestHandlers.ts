import uuid = require("uuid");
import http = require("http");
import { marked } from "marked";
import createDomPurify from "dompurify";
import { JSDOM } from "jsdom";
import prisma from "./prismaBd";
import { generateToken } from "./utils/generateToken";
import MarkdownIt = require("markdown-it");
const dompurify = createDomPurify(new JSDOM().window as unknown as Window);
export async function registration(
  response: http.ServerResponse,
  body: Map<string, any>,
  cookie: Map<string, any>
) {
  const user = await prisma.user.findFirst({
    where: {
      OR: [{ login: body.get("login") }, { mail: body.get("mail") }],
    },
  });
  let dataOfItem;
  if (user) {
    dataOfItem = global.JSON.stringify({ check: false });
  } else {
    const newUser = await prisma.user.create({
      data: {
        mail: body.get("mail"),
        login: body.get("login"),
        password: body.get("pass"),
        token: uuid.v4(),
      },
    });
    dataOfItem = global.JSON.stringify({
      check: true,
      uid: newUser.id,
      token: generateToken(newUser),
      name: newUser.login,
      role: newUser.Admin,
    });
  }
  response.writeHead(200, { "Content-Type": "application/json" });
  response.end(dataOfItem);
}

export async function delUser(
  response: http.ServerResponse,
  body: Map<string, any>,
  cookie: Map<string, any>
) {
  await prisma.user.update({
    where: {
      id: Number(body.get("user")),
    },
    data: {
      del: true,
    },
  });

  response.writeHead(200, { "Content-Type": "application/json" });
  response.end(global.JSON.stringify({ res: true }));
}

export async function delBlog(
  response: http.ServerResponse,
  body: Map<string, any>,
  cookie: Map<string, any>
) {
  await prisma.blog.update({
    where: { id: Number(body.get("bid")) },
    data: {
      del: true,
    },
  });
  response.writeHead(200, { "Content-Type": "application/json" });
  response.end(global.JSON.stringify({ id: body.get("id") }));
}

export async function autorization(
  response: http.ServerResponse,
  body: Map<string, any>,
  cookie: Map<string, any>
) {
  const user = await prisma.user.findFirst({
    where: { mail: body.get("login") },
  });
  let dataOfItem;

  if (user && user.password === body.get("pass") && user.del===false) {
    dataOfItem = global.JSON.stringify({
      check: true,
      uid: user.id,
      token: generateToken(user),
      name: user.login,
      role: user.Admin,
    });
  } else {
    dataOfItem = global.JSON.stringify({ check: false });
  }
  response.writeHead(200, { "Content-Type": "application/json" });
  response.end(dataOfItem);
}

export async function updateArticle(
  response: http.ServerResponse,
  body: Map<string, any>,
  cookie: Map<string, any>
) {

  const html = dompurify.sanitize(await marked.parse(body.get("body")));
  await prisma.user.update({
    where: { id: Number(cookie.get("uid")) },
    data: {
      blogs: {
        update: {
          where: {
            id: Number(body.get("id")),
          },
          data: {
            title: body.get("title"),
            text: html,
          },
        },
      },
    },
  });
  response.writeHead(200, { "Content-Type": "application/json" });
  response.end(global.JSON.stringify({ id: body.get("id") }));
}

export async function sub(
  response: http.ServerResponse,
  body: Map<string, any>,
  cookie: Map<string, any>
) {
  const user = await prisma.user.findUnique({
    where: {
      id: Number(cookie.get("uid")),
    },
    include: {
      subscriptions: true,
    },
  });

  if (user !== null) {
    let isNew = true;
    for (let i = 0; i < user.subscriptions.length; i++) {
      const suba = user.subscriptions[i];
      if (suba.userId === Number(body.get("user"))) {
        isNew = false;
        break;
      }
    }

    if (isNew) {
      await prisma.subscriptions.create({
        data: {
          userId: Number(body.get("user")),
          subId: Number(cookie.get("uid")),
          del: false,
        },
      });
    } else {
      await prisma.subscriptions.updateMany({
        where: {
          userId: Number(body.get("user")),
          subId: Number(cookie.get("uid")),
        },
        data: {
          del: false,
        },
      });
    }
  }

  response.writeHead(200, { "Content-Type": "application/json" });
  response.end(global.JSON.stringify({ res: true }));
}

export async function unsub(
  response: http.ServerResponse,
  body: Map<string, any>,
  cookie: Map<string, any>
) {
  await prisma.subscriptions.updateMany({
    where: {
      userId: Number(body.get("user")),
      subId: Number(cookie.get("uid")),
    },
    data: {
      del: true,
    },
  });

  response.writeHead(200, { "Content-Type": "application/json" });
  response.end(global.JSON.stringify({ res: true }));
}

export async function addArticle(
  response: http.ServerResponse,
  body: Map<string, any>,
  cookie: Map<string, any>
) {
  const html = dompurify.sanitize(await marked.parse(body.get("body")));
  const user = prisma.user.findUnique({ where: { id: body.get("uid") } });
  if (user !== null) {
    const blog = await prisma.blog.create({
      data: {
        title: body.get("title"),
        text: html,
        User: {
          connect: { id: Number(body.get("uid")) },
        },
      },
    });
    response.writeHead(200, { "Content-Type": "application/json" });
    response.end(global.JSON.stringify({ id: blog.id }));
    return;
  }
  response.writeHead(404, { "Content-Type": "application/json" });
  response.end(global.JSON.stringify({ res: false }));
}

export async function addUserToChat(
  response: http.ServerResponse,
  userId: any,
  chatId: any,
  end = true,
  first = false
) {
  const user = await prisma.user.findUnique({ where: { id: Number(userId) } });
  if (user === null) {
    if (end) {
      response.writeHead(401, { "Content-Type": "application/json" });
      response.end(global.JSON.stringify({ id: chatId }));
    }
    return;
  }
  const chat = await prisma.chat.findUnique({
    where: {
      id: Number(chatId),
    },
    include: {
      users: true,
    },
  });

  let inChat = false;
  if (chat !== null) {
    for (let i = 0; i < chat.users.length; i++) {
      if (chat.users[i].userId === Number(userId)) {
        inChat = true;
        break;
      }
    }
  }

  if (inChat || chat === null) {
    if (end) {
      response.writeHead(402, { "Content-Type": "application/json" });
      response.end(global.JSON.stringify({ id: chatId }));
    }
    return;
  }

  if (chat.type === 1 || first) {
    await prisma.usersInChat.create({
      data: {
        unread: 2,
        user: {
          connect: { id: Number(userId) },
        },
        chat: {
          connect: { id: Number(chatId) },
        },
      },
    });
  }
  if (end) {
    response.writeHead(200, { "Content-Type": "application/json" });
    response.end(global.JSON.stringify({ id: chatId }));
  }
}

export async function addToChat(
  response: http.ServerResponse,
  body: Map<string, any>,
  cookie: Map<string, any>
) {
  const user = await prisma.user.findFirst({
    where: { login: body.get("uid") },
  });
  if (user !== null) {
    await addUserToChat(response, user.id, body.get("chat"), true, true);
  } else {
    response.writeHead(401, { "Content-Type": "application/json" });
    response.end(global.JSON.stringify({ id: body.get("chat") }));
  }
}

export async function addChat(
  response: http.ServerResponse,
  body: Map<string, any>,
  cookie: Map<string, any>
) {
  const user = await prisma.user.findUnique({
    where: {
      id: Number(body.get("user")),
    },
    include: {
      chats: {
        include: {
          chat: {
            include: {
              users: true,
            },
          },
        },
      },
    },
  });
  const me = await prisma.user.findUnique({
    where: { id: Number(cookie.get("uid")) },
  });
  if (user === null || me === null) {
    response.writeHead(400, { "Content-Type": "application/json" });
    response.end(global.JSON.stringify({ id: -1 }));
    return;
  }
  const name = `${user.login} - ${me.login}`;
  let hasChat = false;

  for (let i = 0; i < user.chats.length; i++) {
    const chat = user.chats[i];
    if (chat.chat.type !== 0) continue;
    const usersIn = await chat.chat.users;
    for (let j = 0; j < usersIn.length; j++) {
      const userIn = usersIn[j];
      if (userIn.userId === me.id) {
        hasChat = true;
        break;
      }
    }
  }

  if (hasChat) {
    response.writeHead(400, { "Content-Type": "application/json" });
    response.end(global.JSON.stringify({ id: -1 }));
    return;
  }

  const newChat = await prisma.chat.create({
    data: {
      type: 0,
      name,
    },
  });
  await addUserToChat(response, body.get("user"), newChat.id, false, true);
  await addUserToChat(response, cookie.get("uid"), newChat.id, true, true);
}

export async function addGroupChat(
  response: http.ServerResponse,
  body: Map<string, any>,
  cookie: Map<string, any>
) {
  const chat = await prisma.chat.create({
    data: {
      name: body.get("name"),
      type: 1,
    },
  });
  addUserToChat(response, cookie.get("uid"), chat.id, true, true);
}

export async function addComment(
  response: http.ServerResponse,
  body: Map<string, any>,
  cookie: Map<string, any>
) {
  const comment = await prisma.comment.create({
    data: {
      text: body.get("text"),
      User: {
        connect: { id: Number(cookie.get("uid")) },
      },
      blog: {
        connect: { id: Number(body.get("bid")) },
      },
    },
  });
  response.writeHead(200, { "Content-Type": "application/json" });
  response.end(global.JSON.stringify({ comment }));
}
