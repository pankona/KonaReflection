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


# LICENSE

The MIT License (MIT)

Copyright (c) 2015 pankona

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
