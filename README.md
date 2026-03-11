可以，下面给你一版**全中文统一**的 `README.md`，你直接复制到仓库根目录的 `README.md` 里就行。

````markdown
# ros2-tf-demos

一个基于 **ROS 2 Jazzy** 的 TF 学习与演示工作空间，包含 **C++** 和 **Python** 两套示例，用于练习和测试坐标变换（Transform）的发布与监听。

本仓库目前包含两个功能包：

- `demo_cpp_tf`：使用 `rclcpp` 编写的 TF 示例
- `demo_python_tf`：使用 `rclpy` 编写的 TF 示例

项目主要涵盖以下内容：

- 静态坐标变换发布
- 动态坐标变换发布
- 坐标变换监听与查询

---

## 项目结构

```text
ros2-tf-demos/
├── src/
│   ├── demo_cpp_tf/
│   └── demo_python_tf/
└── .gitignore
````

---

## 功能说明

### demo_cpp_tf

C++ 功能包中包含以下节点：

* `static_tf_broadcaster`
* `dynamic_tf_broadcaster`
* `tf_listener`

主要用于演示：

* 发布静态坐标变换
* 发布动态坐标变换
* 监听并查询不同坐标系之间的变换关系

### demo_python_tf

Python 功能包中包含以下节点：

* `static_tf_broadcaster`
* `dynamic_tf_broadcaster`
* `tf_listener`

主要用于演示：

* 使用 Python 发布静态 TF
* 使用 Python 发布动态 TF
* 周期性查询 TF 并输出位姿信息

---

## 环境要求

* Ubuntu
* ROS 2 Jazzy
* colcon
* 已配置好的 ROS 2 C++ / Python 开发环境

---

## 构建方法

将本仓库作为一个 ROS 2 工作空间使用，在仓库根目录执行：

```bash
colcon build
source install/setup.bash
```

如果只想单独构建这两个功能包，也可以执行：

```bash
colcon build --packages-select demo_cpp_tf demo_python_tf
source install/setup.bash
```

---

## 运行方法

### 运行 C++ 静态 TF 发布节点

```bash
ros2 run demo_cpp_tf static_tf_broadcaster
```

### 运行 C++ 动态 TF 发布节点

```bash
ros2 run demo_cpp_tf dynamic_tf_broadcaster
```

### 运行 C++ TF 监听节点

```bash
ros2 run demo_cpp_tf tf_listener
```

### 运行 Python 静态 TF 发布节点

```bash
ros2 run demo_python_tf static_tf_broadcaster
```

### 运行 Python 动态 TF 发布节点

```bash
ros2 run demo_python_tf dynamic_tf_broadcaster
```

### 运行 Python TF 监听节点

```bash
ros2 run demo_python_tf tf_listener
```

---

## TF 可视化与调试

可以使用以下命令查看当前 TF 树：

```bash
ros2 run tf2_tools view_frames
```

如果系统中安装了对应工具，也可以使用图形界面方式查看 TF 关系。

---

## 学习目标

这个仓库主要用于：

* 学习 ROS 2 中 TF 的基础用法
* 理解父坐标系与子坐标系之间的关系
* 对比 C++ 与 Python 两种实现方式
* 练习坐标变换的发布、监听与查询流程

---

## 当前状态

这是一个用于学习和练手的演示项目，目前仍在持续完善中。

部分功能、依赖配置和说明文档后续还可以继续优化，但整体结构已经能够用于 TF 基础学习和代码整理。

---

## License

Apache-2.0