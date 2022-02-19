### 关于FLTK的配置

FLTK的配置我折腾了好久，一晚上的折腾终于搭建好了编译环境，最后总结出一下几个关键点：

- 【Info】使用的配置 window10，Visual Studio 2022。（即使是最新版的也没有问题）
- 进入官网下载FLTK库的时候，经过测试版本1.3.7、1.3.4都没有问题，所以选择新的也可以。下载到一个特定的位置【记住就行】
- 打开IDE文件夹，再打开`.sln` 后缀的文件，进入 Visual Studio 2022的页面
- 提示选择配置，注意，这个时候不要选择最新的配置，否则会报错，例如下图，请一定选择 `10.0.18362 ` 选择完点确定

![image](https://user-images.githubusercontent.com/84625273/154788138-b933f7f6-2a5e-4a69-8f08-c88dd09a0008.png)

- 单机 `生成->生成解决方案` 即可。等待时间很长。
- 一段时间后会提示`生成79个文件，成功79个，错误0个` 方可关闭程序
- 打开下载的FLTK源文件，进入`lib` 文件夹，把里面的所有 `lib` 的文件，理论有14个，因为 `debug` `release` 模式下的各有七个静态链接库文件，这十四个文件都要拷贝走。
- 此外 `FL\` 这个文件夹也要拷贝走，拷贝到哪里请看后文。
- 拷贝到哪里？拷贝到Visual Studio 2022安装目录，我的是`D:\Program Files\Microsoft Visual Studio\2022\Community\VC\Tools\MSVC`
- 但是你可能会发现这个文件夹里面有好几个版本号的文件夹，如果不清楚，请对所有的文件夹执行下面的操作
  - `include` 文件夹里面放置 `FL\` 这个文件夹，没错，整个 `FL\` 这个文件夹一起拷贝走。
  - `lib` 文件夹里面放置所有的14个 `lib` 的文件，可能会遇到`x86`  `x64` 的文件夹的情况，如果不确定，直接把所有的14个 `lib` 的文件在`x86`  `x64` 的文件夹这两个文件夹里面都拷贝一份，就是分别移动到`x86`  `x64` 的文件夹
- 完成后，创建一个**空项目**！！！visual studio的空项目！！！必须是空项目，看图。空项目->C++

![image](https://user-images.githubusercontent.com/84625273/154788149-72a0f28c-0df0-49fa-8de7-6e51fa763afd.png)

- 创建后，创建一个`main` 的源文件。
- 再按照下图配置，对比就是了！特别注意，**所有配置！！！所有平台！！！**

![image](https://user-images.githubusercontent.com/84625273/154788155-aa3375c0-d410-4338-9ef3-28eee865ec0a.png)

- 特别注意 这里的附加依赖项！！！修改一下

```
fltkd.lib
wsock32.lib
comctl32.lib
fltkjpegd.lib
fltkimagesd.lib
```

![image](https://user-images.githubusercontent.com/84625273/154788161-79b79c9e-e822-4181-8225-5c628c1733c5.png)

- 最后运行测试代码
