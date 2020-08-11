<h1 align="center">Welcome to Linux System Monitor 👋</h1>
<p>
  <a href="LICENSE" target="_blank">
    <img alt="License: MIT" src="https://img.shields.io/badge/License-MIT-yellow.svg" />
  </a>
  <a href="https://twitter.com/mbrsantana" target="_blank">
    <img alt="Twitter: mbrsantana" src="https://img.shields.io/twitter/follow/mbrsantana.svg?style=social" />
  </a>
</p>

> Linux system monitor project like htop

![System Monitor](.github/monitor.png)

Starter code for System Monitor Project in the Object Oriented Programming Course of the [Udacity C++ Nanodegree Program](https://www.udacity.com/course/c-plus-plus-nanodegree--nd213). 

## Dependencies for Running Locally
[ncurses](https://www.gnu.org/software/ncurses/) is a library that facilitates text-based graphical output in the terminal. This project relies on ncurses for display output.

Install ncurses within your Linux environment: `sudo apt install libncurses5-dev libncursesw5-dev`

## Make
This project uses [Make](https://www.gnu.org/software/make/). The Makefile has four targets:
* `build` compiles the source code and generates an executable
* `format` applies [ClangFormat](https://clang.llvm.org/docs/ClangFormat.html) to style the source code
* `debug` compiles the source code and generates an executable, including debugging symbols
* `clean` deletes the `build/` directory, including all of the build artifacts

## Instructions

1. Clone the project repository: `git clone https://github.com/zerocoolbr/Linux-System-Monitor.git`

2. Build the project: `make build`

3. Run the resulting executable: `./build/monitor`

4. Enjoy!

## Author

👤 **Marcos Santana**

* Twitter: [@mbrsantana](https://twitter.com/mbrsantana)
* Github: [@zerocoolbr](https://github.com/zerocoolbr)
* LinkedIn: [@marcosbrs](https://linkedin.com/in/marcosbrs)

## Show your support

Give a ⭐️ if this project helped you!

## 📝 License

Copyright © 2020 [Marcos Santana](https://github.com/zerocoolbr).<br />
This project is [MIT](LICENSE) licensed.