# SocialNetworks

# 数据结构实践12

## 主要文件结构

* `SocialNetworks`
  * `Graph.h`
  * `Graph.cpp`
  * `Node.h`
  * `Stack.h`
  * `Instructor.h`
  * `Instructor.cpp`
  * `utility.h`
  * `utility.cpp`
  * `Main.cpp`
  * `relation.dat`
* `SocialNetworks.sln`
  
# 运行方法

通过Visual Studio 2022打开`SocialNetworks.sln`，编译并运行，然后按照程序提示输入对应的人物关系即可

## 输入示例：

### 添加关系

```
Ping is Xiang Ling's master.
Ping is Traveler's good friend.
Xiang Ling and Traveler are good friends.
Xiang Ling and Guoba are good friends.
Traveler is Xing Qiu's good friend.
Tighnari is Collei's teacher.
Tighnari and Cyno are friends.
Ayaka is Ayato's sibling.
```

### 询问关系

```
What's the relationship between Ping and Traveler?
What's the relationship between Xiang Ling and Ping?
Is there any relationship between Tighnari and Collei?
Is there any relationship between Ayaka and Ayato?
```

### 查看传播模拟

```
Traveler gets a message.
Xiang Ling gets a message.
```
