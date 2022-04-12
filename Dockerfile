FROM gcc:latest

RUN mkdir /app

WORKDIR /app

COPY . /app

RUN make build

CMD /app/bin/app