[![Build Status](https://travis-ci.org/pankona/KonaReflection.svg?branch=master)](https://travis-ci.org/pankona/KonaReflection)

# このリポジトリは

cocos2d-xを勉強がてら、ブロック崩しを作ってみるという試みのためのリポジトリです。

# ビルド方法

* cocos2dのリポジトリを参照して、cocosコマンドが使える環境を整えます。
* 本リポジトリをクローンします。
* サブモジュールを取得します。

`$ git submodule init`  
`$ git submodule update`  

* cocos2d ディレクトリが出てくるのでそこに入り、再度サブモジュールを取得します。

`$ cd cocos2d`  
`$ git submodule init`  
`$ git submodule update`  

* リポジトリトップディレクトリに戻り、ビルドを実行します。  
Mac向け、Linux向け、Android向けのビルドがいまのところ有効です。
  
`$ cocos compile -p linux` Linux向け  
`$ cocos compile -p mac` Mac向け  
`$ cocos compile -p android` Android向け  

