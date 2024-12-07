# # Stage 1: Build the React app
# FROM node:16 as build

# WORKDIR /app

# COPY package.json package-lock.json ./
# RUN npm install

# COPY . ./
# RUN npm run build

# # Stage 2: Serve the React app
# FROM nginx:alpine

# COPY --from=build /app/build /usr/share/nginx/html

# EXPOSE 8081

# CMD ["nginx", "-g", "daemon off;"]

FROM node:18-alpine3.15 as build

RUN apk add --no-cache protoc

WORKDIR /app

ENV protoc_gen_grpc_web=./node_modules/.bin/protoc-gen-grpc-web

COPY . ./

RUN npm install

EXPOSE 8081

CMD ["npm", "start"]
# CMD ["npm", "start"]docker