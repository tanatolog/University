import jwt from 'jsonwebtoken';
import { User } from '@prisma/client';


export  function generateToken (user: User) {
  return jwt.sign({ id: user.id,login:user.login, email: user.mail,admin:user.Admin}, process.env.JWT_SECRET!,{expiresIn:"1h"});
}
export  function checkToken (token: string) {
  return  jwt.verify(token, process.env.JWT_SECRET!);
}