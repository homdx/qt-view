FROM homdx/qt-sources:001-slim

ARG ADBCACHE_VERSION=1.0.8
ARG ADBCACHE_HASH=0fbd85bdfd3619b3ba962b5694c815689e6629bc1bc551f267ff9c37025ee2f6d7941f390b77cde63dc677e155c86f36dd23ee5aaf829e6ae8a25d1c0226234f
ARG ADBCACHEFILE=android1.tar.gz

RUN cd /root && set -ex && curl -s -L -o android.tar.gz https://github.com/homdx/qt-view/releases/download/${ADBCACHE_VERSION}/${ADBCACHEFILE} \
    && echo "${ADBCACHE_HASH}  android.tar.gz" | sha512sum -c \
    && tar -xf android.tar.gz \
    && ls -la android.tar.gz && cd ..

ARG projname=qt-view
ARG profile=qt-stackview.pro

ADD . /app/qt-view/

WORKDIR /app/qt-view/src

RUN export ANDROID_TARGET_SDK_VERSION=28 && \
export NDK_VERSION=r19c && \
export    ANDROID_NDK_ARCH=arch-arm c && \
export    ANDROID_NDK_EABI=llvm c && \
export    ANDROID_NDK_HOST=linux-x86_64 c && \
export    ANDROID_NDK_TOOLCHAIN_PREFIX=arm-linux-androideabi c && \
export    ANDROID_NDK_TOOLCHAIN_VERSION=4.9 c && \
export DEBIAN_FRONTEND=noninteractive c && \
export PATH=/usr/local/Qt-5.13.1/bin:$PATH && \
    echo make translations && lrelease ${profile} && \
    qmake ${profile} && echo qmake done  && build-android-gradle-project ${profile} --debug && \
    echo copy result apk && \
    cp -vf android-build/build/outputs/apk/debug/android-build-debug.apk /app

CMD tail -f /var/log/faillog
