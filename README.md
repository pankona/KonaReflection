[![Build Status](https://travis-ci.org/pankona/KonaReflection.svg?branch=master)](https://travis-ci.org/pankona/KonaReflection)

# このリポジトリは

cocos2d-xを勉強がてら、ブロック崩しを作ってみるという試みのためのリポジトリです。

# ビルド方法

* cocos2dのリポジトリを参照して、cocosコマンドが使える環境を整えます。

  * 本リポジトリをクローンします。
  * ソースツリー内にて以下のコマンドを入力。サブモジュールを取得します。

`$ git submodule update --init --recursive`  

  * `src/cocos2d` にcocos2d-xのソースが一式現れるので、cocosコマンドが使えるように設定します。
  詳しくは[cocos2dの公式リポジトリの説明](https://github.com/cocos2d/cocos2d-x)で確認してね。

* cocos2コマンドによるビルドを実行します。  
Mac向け、Linux向け、Android向けのビルドがいまのところ有効です。
  
`$ cocos compile -p linux` Linux向け  
`$ cocos compile -p mac` Mac向け  
`$ cocos compile -p android` Android向け


