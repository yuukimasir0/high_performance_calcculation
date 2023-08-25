#include <pthread.h> 
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define NUM_THREADS 10

void *thread_func(void *arg) {
    int id = (int)arg; //(1)
    for (int i = 0; i < 5; i++) {
        printf("id = %d, i = %d\n", id, i);
        sleep(1);
    }

    return "finished!";
}

//デタッチスレッドの作成

int main(int argc, char *argv[]) {
    pthread_attr_t attr;
    //アトリビュートの初期化
    if(pthread_attr_init(&attr) != 0) {
        perror("pthread_attr_init");
        return -1;
    }

    //アトリビュートをデタッチスレッドに設定
    if(pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED) != 0) {
        perror("pthread_attr_setdetachstate");
        return -1;
    }

    pthread_t th; // スレッド用のハンドラを保存する配列。

    //スレッドの生成 アトリビュートを指定
    if(pthread_create(&th, &attr, thread_func, NULL) != 0) { 
        perror("pthread_create");
        return -1;
    }

    //アトリビュートの破棄
    if(pthread_attr_destroy(&attr) != 0) {
        perror("pthread_attr_destroy");
        return -1;
    }

    sleep(7);

    return 0;
}