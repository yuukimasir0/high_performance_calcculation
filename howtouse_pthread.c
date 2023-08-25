#include <pthread.h> //Pthreadsを使う場合はインクルード
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define NUM_THREADS 10

/**
実際にスレッドとなる関数
@param arg: void* 
@return void*
注意: 入出力の型は上記の物である必要がある。そのため、入力などは関数内で適切にキャストする必要がある(1)。

 サンプル: idをうけとり各id毎に5回ループをして出力、各ループ毎に1secスリープをはさむ。
**/
void *thread_func(void *arg) {
    int id = (int)arg; //(1)
    for (int i = 0; i < 5; i++) {
        printf("id = %d, i = %d\n", id, i);
        sleep(1);
    }

    return "finished!";
}

int main(int argc, char *argv[]) {
    pthread_t v[NUM_THREADS]; //スレッド用のハンドラを保存する配列。

    for (int i = 0; i < NUM_THREADS; i++) {
        if(pthread_create(&v[i], NULL, thread_func, (void *) i) != 0) { //スレッドの生成
            perror("pthread_create");
            return -1;
        }
    }
    

    for (int i = 0; i < NUM_THREADS; i++) {
        char *ptr;
        if(pthread_join(v[i], (void**)&ptr) == 0) { //スレッド終了待機
            printf("msg = %s\n", ptr);
        } else {
            perror("pthread_join");
            return -1;
        }
    }

    return 0;
}