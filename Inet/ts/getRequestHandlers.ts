import fs = require("fs");
import ejs = require("ejs");
import uuid = require("uuid");
import http = require("http");
import amqp = require("amqplib/callback_api");

import prisma from "./prismaBd";

function notFound(res: http.ServerResponse) {
  res.statusCode = 404;
  res.setHeader("Content-Type", "text/plain");
  res.end("NOT FOUND 404\n");
}

export function send404(res: http.ServerResponse) {
  fs.readFile(`${__dirname}/../src/403.html`, "utf-8", (err, file) => {
    if (err) {
      notFound(res);
      return;
    }
    res.write(file);
    res.end();
  });
}

function sendFile(
  filename: string,
  res: http.ServerResponse,
  data: Record<string, any>
) {
  fs.readFile(filename, "utf-8", (err, file) => {
    if (err) {
      console.error(err);
      notFound(res);
      return;
    }
    res.write(ejs.render(file, data));
    res.end();
  });
}

export async function getUserData(
  res: http.ServerResponse,
  myUid: number,
  pageUid: number,
  role: boolean
) {
  let page = pageUid;
  if (typeof pageUid === "undefined") {
    page = myUid;
  }

  if (typeof page === "undefined") {
    send404(res);
    return;
  }

  const user = await prisma.user.findUnique({
    where: {
      id: Number(page),
    },
    include: {
      blogs: true,
    },
  });

  if (user !== null && !user.del) {
    let myPage = true;
    let suber = false;
    let hasChat = false;
    let chatId = 0;
    if (myUid !== page && typeof myUid !== "undefined") {
      const me = await prisma.user.findUnique({
        where: {
          id: Number(myUid),
        },
        include: {
          subscriptions: true,
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
      if (me !== null) {
        myPage = false;
        for (let i = 0; i < me.subscriptions.length; i++) {
          const sub = me.subscriptions[i];
          if (sub.userId === Number(page) && sub.del !== true) {
            suber = true;
          }
        }

        for (let i = 0; i < me.chats.length; i++) {
          const { chat } = me.chats[i];
          if (chat.type !== 0) continue;
          const usersIn = chat.users;
          for (let j = 0; j < usersIn.length; j++) {
            const userIn = usersIn[j];
            if (userIn.userId === Number(myUid)) {
              hasChat = true;
              chatId = chat.id;
              break;
            }
          }
        }
      }
    }

    const mes = {
      user,
      me: { myUid, role },
      myPage,
      sub: suber,
      hasChat,
      chat: chatId,
    };
    sendFile(`${__dirname}/../views/user.ejs`, res, mes);
    return;
  }
  send404(res);
}

export async function getBlog(
  res: http.ServerResponse,
  id: number,
  uid: number,
  role: boolean
) {
  const blog = await prisma.blog.findUnique({
    where: {
      id: Number(id),
    },
    include: {
      User: true,
      comments: {
        include: {
          User: true,
        },
      },
    },
  });
  if (blog && !blog.del) {
    const mes = { blog, me: { uid, role } };
    sendFile(`${__dirname}/../views/blog.ejs`, res, mes);
  } else {
    send404(res);
  }
}

export function addBlog(res: http.ServerResponse, uid: number) {
  if (typeof uid === "undefined") {
    send404(res);
  } else {
    const mes = {
      blog: { title: "new title", text: "# new text" },
      me: uid,
      type: 0,
    };
    sendFile(`${__dirname}/../views/new_blog.ejs`, res, mes);
  }
}

export async function updateBlog(
  res: http.ServerResponse,
  id: number,
  uid: number
) {
  if (typeof uid === "undefined") {
    send404(res);
  } else {
    const blog = await prisma.blog.findUnique({ where: { id: Number(id) } });
    if (blog) {
      const mes = { blog, me: uid, type: 1 };
      sendFile(`${__dirname}/../views/new_blog.ejs`, res, mes);
    } else {
      send404(res);
    }
  }
}

export async function getBlogs(
  res: http.ServerResponse,
  size: number,
  page: number,
  uid: number
) {
  let newPage = page;
  if (page < 1) {
    newPage = 1;
  }
  const first = (newPage - 1) * size;
  const blogs = await prisma.blog.findMany({
    skip: first,
    take: size,
    where: { del: false },
  });
  const mes = { blogs, me: uid, page: newPage, header: "Все блоги" };
  sendFile(`${__dirname}/../views/blogs.ejs`, res, mes);
}

export async function getMySubs(
  res: http.ServerResponse,
  size: number,
  page: number,
  uid: number
) {
  if (typeof uid === "undefined") {
    send404(res);
    return;
  }
  let newPage = page;
  if (page < 1) {
    newPage = 1;
  }

  const first = (newPage - 1) * size;

  const subs = await prisma.subscriptions.findMany({
    where: {
      subId: Number(uid),
    },
  });

  const uids = new Array<number>();
  subs.forEach((sub: any) => {
    if (!sub.del) uids.push(sub.userId);
  });

  const blogs = await prisma.blog.findMany({
    where: {
      userId: {
        in: uids.map((user) => user),
      },
      del:false 
    },
    skip: first,
    take: size,
    
  });
  const mes = { blogs, me: uid, page, header: "Мои подписки" };
  sendFile(`${__dirname}/../views/blogs.ejs`, res, mes);
}

export async function getChats(res: http.ServerResponse, userId: number) {
  if (typeof userId === "undefined") {
    send404(res);
    return;
  }
  const user = await prisma.user.findUnique({
    where: {
      id: Number(userId),
    },
    include: {
      chats: {
        include: {
          chat: true,
        },
      },
    },
  });
  if (user === null) {
    send404(res);
    return;
  }

  const mes = { user, me: userId };
  sendFile(`${__dirname}/../views/chats.ejs`, res, mes);
}

export async function getChatInfo(
  res: http.ServerResponse,
  chatId: number,
  userId: number
) {
  const chat = await prisma.chat.findUnique({
    where: {
      id: Number(chatId),
    },
    include: {
      users: {
        include: {
          user: true,
        },
      },
    },
  });
  if (chat === null) {
    send404(res);
    return;
  }

  let inChat = false;

  for (let i = 0; i < chat.users.length; i++) {
    const user = chat.users[i];
    if (user.userId === Number(userId)) {
      inChat = true;
      break;
    }
  }

  if (inChat) {
    const mes = { chat, me: userId };
    sendFile(`${__dirname}/../views/chat_info.ejs`, res, mes);
  } else {
    send404(res);
  }
}

export async function getChatAndLast(
  res: http.ServerResponse,
  chatId: number,
  userId: number
) {
  const chat = await prisma.chat.findUnique({
    where: {
      id: Number(chatId),
    },
    include: {
      messages: {
        include: {
          User: true,
        },
      },
      users: {
        include: {
          user: true,
        },
      },
    },
  });
  if (chat === null) {
    send404(res);
    return;
  }

  let inChat = false;
  for (let i = 0; i < chat.users.length; i++) {
    const user = chat.users[i];
    if (user.userId === Number(userId)) {
      inChat = true;
      break;
    }
  }

  if (inChat) {
    const mes = { chat, me: userId };
    sendFile(`${__dirname}/../views/chat.ejs`, res, mes);
  } else {
    send404(res);
  }
}

export async function addMessage(chat: any, user: any, text: string) {
  await prisma.message.create({
    data: {
      userId: Number(user),
      chatId: Number(chat),
      text,
    },
  });
}

export async function checkAndAddChat(
  ws: any,
  chatId: any,
  userId: any,
  name: string
) {
  const chat = await prisma.chat.findUnique({
    where: {
      id: Number(chatId),
    },
    include: {
      users: {
        include: {
          user: true,
        },
      },
    },
  });
  if (chat === null) {
    return;
  }

  let inChat = false;
  for (let i = 0; i < chat.users.length; i++) {
    const user = chat.users[i];
    if (user.userId === Number(userId)) {
      inChat = true;
      break;
    }
  }

  if (inChat) {
    addToChat(ws, chatId, userId, name);
  }
}

const wsChats = new Array<any>();
let myChannel: amqp.Channel | null = null;

export function addToChat(ws: any, chat: any, uid: any, name: string) {
  if (!Object.prototype.hasOwnProperty.call(wsChats, chat)) {
    const chatObj = {};
    createQueue(chat);
    wsChats[chat] = chatObj;
  }
  const myUuid = uuid.v4();
  wsChats[chat][myUuid] = ws;
  ws.uid = uid;
  ws.uuid = myUuid;
  ws.name = name;
  ws.chat = chat;
}

export function removeFromChat(ws: any) {
  if (Object.prototype.hasOwnProperty.call(ws, "chat")) {
    delete wsChats[ws.chat][ws.uuid];
    let last = true;
    for (const key in wsChats[ws.chat]) {
      last = false;
      break;
    }

    // console.log(`lenght ${wsChats[ws.chat].length}`);
    // console.log(`lenght ${wsChats[ws.chat]}`);
    if (last) {
      if (myChannel !== null) {
        myChannel.deleteQueue(ws.chat);
      }
      delete wsChats[ws.chat];
    }
  }
}

export function sendMessage(ws: any, data: any) {
  if (Object.prototype.hasOwnProperty.call(ws, "chat")) {
    const json = JSON.parse(data);
    const mes = JSON.stringify({
      name: ws.name,
      from: ws.uid,
      text: json.text,
    });
    if (myChannel !== null) {
      myChannel.sendToQueue(ws.chat, Buffer.from(mes));
    }
    // for (const key in wsChats[ws.chat]) {
    //   wsChats[ws.chat][key].send(
    //     JSON.stringify({ name: ws.name, from: ws.uid, text: json.text })
    //   );
    // }
    addMessage(ws.chat, ws.uid, json.text);
  }
}

function createQueue(name: string) {
  if (myChannel === null) return null;
  myChannel.assertQueue(
    name,
    {
      autoDelete: true,
    },
    function (error2, q) {
      if (myChannel === null) return null;
      if (error2) {
        throw error2;
      }

      myChannel.bindQueue(q.queue, "direct_logs", "");

      myChannel.consume(
        q.queue,
        function (msg) {
          if (msg !== null) {
            for (const key in wsChats[Number(name)]) {
              wsChats[Number(name)][key].send(msg.content.toString());
            }
          }
        },
        {
          noAck: true,
        }
      );
    }
  );
}

amqp.connect("amqp://localhost", function (error0, connection) {
  if (error0) {
    throw error0;
  }
  connection.createChannel(function (error1, channel) {
    if (error1) {
      throw error1;
    }
    myChannel = channel;
    channel.assertExchange("direct_logs", "direct", {
      durable: false,
    });
  });
});
