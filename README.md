[ふつうの Linux プログラミング　第二版](https://www.sbcr.jp/product/4797386479/)のコード置き場

## 使い方

```shell
docker compose up -d
docker compose exec -it ordinaryLinuxProgramming /bin/bash
// コンテナ内でCのコードを実行する
gcc -o hello hello.c
./hello
```
