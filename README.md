# exec_cli
一个可在命令行执行PHP脚本的扩展，支持后台执行

----------------------------------------------------------------------------------

http连接最大执行30秒，此扩展在CLI端执行其它php脚本，以另一种简单方法解决PHP长时间操作


## 编译安装：

PHP扩展常规安装方法

## 其它

- 只允许执行PHP文件

## 使用方法

```php
<?php

// 后台执行
// 第二个参数为执行PHP脚本传递的字符串参数，可传json
// 第三个参数为 是否后台，默认是
exec_cli('/www/index.php', 's=1&s=2');

// 同步执行并返回
// 第三个参数为 是否后台，否则直接执行完成后直接返回结果
$result = exec_cli('/www/index.php', '', false);

?>
```
