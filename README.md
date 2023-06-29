# Commandline Sudoku

这是一个可以生成和解答数独游戏的程序。

## Quick Start

- 在主目录下使用以下命令编译
  
````
  make
````

- 在进入build/目录，运行shudu.exe，可通过以下参数实现不同需求（斜体字应被替换为您设置的数字或路径）
    - -c *number* &emsp; 生成*number*个数独终盘，*number*范围是1-1000000
    - -s *path* &emsp; &emsp; 从*path*中读取若干个数独游戏，给出解答，默认输出到sudoku.txt中
    - -n *number* &emsp; 生成*number*个数独游戏，*number*范围是1-10000
    - -m *level* &emsp; &emsp;生成若干个难度为*level*的数独游戏, *level*范围1-3，必须与-n一同使用
    - -r *number1* *number2* &emsp;生成若干个挖空数在*number1*-*number2*之间的数独游戏，必须与-n一同使用
    - -u &emsp; &emsp; &emsp; &emsp; 生成若干个有唯一解的数独游戏，必须与-n一同使用

![options](img_v2_3d497d21-4027-4808-81ae-995b82b3533g.png)


- 还可以使用make在主目录下运行程序
````
make test ARGS="-c 10"
````

- 使用以下命令清除已有的目标文件
````
make clean
````

## 注意事项

- 用make编译
    - 目标可执行文件是build/shudu
    - make test 运行程序，例：make test ARGS="-c 2"


- sudoku.h: 数独生成和求解的一系列代码
    - Sudoku::to_string产生朴素字符串，可用于文件读写
    - Sudoku::to_pretty_string产生高可读性的字符串
    - 其余请看注释

## TODO

- generate_m和generate_u
- 解析参数
- 文件读写