import { BuildOptions, DataTypes, Model, Sequelize } from "sequelize";

export = new Sequelize("site", "postgres", "Admin", {
  logging: false,
  dialect: "postgres",
  host: "127.0.0.1",
  port: 5438,
});
