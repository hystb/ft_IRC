FROM debian:latest
WORKDIR /app
RUN apt-get update && apt-get install -y make && apt-get install -y clang
COPY . .
RUN make
CMD ["./ircserv", "4000", "lol"]
EXPOSE 4000
