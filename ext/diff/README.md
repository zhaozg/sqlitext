# sqlite3 diff and patch tool

Come from [lukas-w/sqlitediff](https://github.com/lukas-w/sqlitediff)
and update(use C replace CPP).

## 使用方法

### 形成差异文件(补丁)

`./sqlite-diff db1 db2 > db.diff`

比较 `db1` 到 `db2` 之间的差异, 形成补丁文件 `db.diff`.
对 `db1` 打补丁文件 `db.diff` 可以形成 `db2`.

### 打补丁

`./sqlite-patch db1 db.diff`

将补丁文件`db.diff`应用到`db1`文件中.

## 如何编译

`mkdir -p build && cd build && cmake .. && make`

## 限制条件

1. db1 与 db2 的库结构, 表结构必须完全相关, 该同步程序仅能对增加的、删除的、修改的数据进行同步处理.
