import { BuildOptions, DataTypes } from "sequelize";
import sequelize = require("./db");

export const user = sequelize.define("user", {
  id: { type: DataTypes.INTEGER, primaryKey: true, autoIncrement: true },
  login: { type: DataTypes.STRING, unique: true },
  mail: { type: DataTypes.STRING, unique: true },
  password: { type: DataTypes.STRING },
  token: { type: DataTypes.STRING },
});

export const blog = sequelize.define("blog", {
  id: { type: DataTypes.INTEGER, primaryKey: true, autoIncrement: true },
  title: { type: DataTypes.STRING },
  text: { type: DataTypes.STRING },
});

export const chat = sequelize.define("chat", {
  id: { type: DataTypes.INTEGER, primaryKey: true, autoIncrement: true },
  name: { type: DataTypes.STRING },
  type: { type: DataTypes.INTEGER },
  userCount: { type: DataTypes.INTEGER },
});

export const comment = sequelize.define("comment", {
  id: { type: DataTypes.INTEGER, primaryKey: true, autoIncrement: true },
  text: { type: DataTypes.STRING },
});

export const message = sequelize.define("message", {
  id: { type: DataTypes.INTEGER, primaryKey: true, autoIncrement: true },
  text: { type: DataTypes.STRING },
});

export const subscription = sequelize.define("subscription", {
  // uid: {type:DataTypes.INTEGER},
  // tid: {type:DataTypes.INTEGER},
  del: { type: DataTypes.BOOLEAN },
});

export const usersInChat = sequelize.define("users_in_chat", {
  unread: { type: DataTypes.INTEGER },
});

user.hasMany(blog);
blog.belongsTo(user);

user.hasMany(comment);
comment.belongsTo(user);

blog.hasMany(comment);
comment.belongsTo(blog);

user.hasMany(message);
message.belongsTo(user);

chat.hasMany(message);
message.belongsTo(chat);

chat.belongsToMany(user, { through: usersInChat });
user.belongsToMany(chat, { through: usersInChat });

user.hasMany(subscription);
subscription.belongsTo(user, { as: "user_id" });
subscription.belongsTo(user, { as: "tid" });

// subscription.hasOne(user, {as:'user_id'});

module.exports = {
  user,
  blog,
  chat,
  message,
  comment,
  usersInChat,
  subscription,
};
