# EGE 24.04 安装包

- 安装教程 <https://xege.org/beginner-lesson-1.html>
- IDE下载 <https://xege.org/install_and_config>
- 源代码 <https://github.com/wysaid/xege>

# 版本更新说明

## 配置变更
- 库文件名统一为 `graphics.lib` 或 `libgraphics.a`
- 在 GCC 中使用 ege 库时，需要链接 `libgraphics.a`, `libgdi32.a`, `libgdiplus.a` 库，参数为 `-lgraphics -lgdi32 -lgdiplus`

## 新特性

- 新增 EGE_VERSION, EGE_VERSION_NUMBER 等版本相关的宏
- 提供 Linux /MacOs 下的编译支持(使用 MinGW-W64 工具链)
- 新增 putimage_rotatetransparent()，支持指定透明色旋转绘制图像
- 新增 putpixel_savealpha(写入像素时保留原来的 alpha 值),
- 新增 putpixel_alphablend(使用 alpha 混合公式写入像素)
- 新增 ege_drawimage()，用于绘制带透明通道图像(支持坐标变换，拉伸)
- 新增控制台系列相关函数(不支持 VC++ 6.0)
- 新增圆角矩形系列函数、填充圆系列函数，饼形系列函数，闭合曲线系列函数，填充矩形(fillrect)
- 新增无边框填充的普通图形函数
- 新增与 drawpoly 相似但更明确的 polyline(折线), polygon(多边形)
- 新增路径图形
- 支持保存带透明通道的 BMP 图片， 新增保存 BMP 格式图片的 savebmp 函数
- 新增 key_A 和 key_Z 中间的键码定义
- 新增更多预定义颜色
- 新增按键标志位 key_flag_first_down，指示按键按下时发送的第一次 down 消息
- 新增 showwindow(), hidewindow() 函数，用于控制窗口显示/隐藏
- 新增 INIT_HIDE 初始化模式，使用窗口创建后不可见(调用 showwindow() 显示窗口)
- 支持在 EGE 中使用 UTF-8 字符串
- 新增用于刷新窗口的 flushwindow() 函数，确保显示绘图内容
- 提供对 VS2022 的支持
- putimage_withalpha() 支持缩放
- ege_系列绘图函数支持设置线型(由 setlinestyle 设置)
- MUSIC 类增加 RepeatPlay(), 支持循环播放
- 新增 alpha 颜色混合计算函数 alphablend(标准公式), colorblend(保留目标颜色的alpha值), alphablend_premultiplied(预乘 alpha 格式)
- 支持设置线帽和线条连接样式
- randomize 支持传入随机数种子，并且会返回所使用的随机数种子
- 新增 ege_系列使用 ARGB 颜色的单行文本输出函数(ege_xyprintf, ege_outtextxy)
- 支持对使用预乘 alpha 像素格式的图像进行混合
- 支持设置和获取 EGE 所使用的代码页
- ege_系列高级绘图函数支持坐标变换
- 支持独立设置和获取线条颜色和文本颜色

## 修复 BUG

- 修复 inputbox_getline() 界面发黑的问题(20.08 引入)
- 修复 sector() 函数在半径小于等于 20 时出现绘制错误的问题
- 修复 drawpoly() 绘制闭合多边形时首尾连接点无拐角的问题
- 修复 setinitmode() 无法改变窗口位置的问题(20.08 引入)
- 修复初始化后 initgraph(-1, -1) 无法将窗口大小设置为全屏的问题
- 修复 sys_edit 的 isfocus() 函数不可用的问题
- 修复 sys_edit 在调用 setfocus() 后不显示光标的问题
- 修复初始化后鼠标初始位置不正确的问题
- 修复 rgb2gray() 未对做近似处理的问题
- 修复用户手动关闭窗口，不能马上退出的问题
- 修复 delay_ms(0) 延时过长的问题，改为与 Sleep(0) 一致的行为(放弃剩余 CPU 时间片，其它线程执行后立即返回)
- 修复角度不为0的文本在设置垂直居中时发生偏移的问题
- 修复 RGB 格式图片文件读取后图像 alpha 通道为 0 的问题
- 修复 ege_drawtext() 无法旋转的问题
- 修复填充模式 EMPTY_FILL 不正确的问题
- 修复矩形区域输出文本无法按照对齐方式正确的问题
- 修复 ege_drawtext() 无法按照指定字体宽度输出文本的问题
- 修复 outtext() 不更新当前点的问题
- 纠正 HOME 键和 END 键的键码
- 修复设置视口后当前点没有移动至视口左上角的问题
- 修复 putimage 系列函数在源矩形区域左上角不为 (0,0) 且宽高使用默认值0时会发生越界的问题
- 修复设置视口后 GDI+ 绘图坐标系未移动至视口左上角的问题
- VECTOR3D 的 GetAngel() 函数纠正为 GetAngle()
- 修复 random() 无默认参数的问题
- 修复 keystate 在打开文件对话窗口后失效的问题

## 功能调整
- getimage() 返回值类型统一为 int, 表示是否成功读取图像
- saveimage() 根据文件名后缀确定保存为 PNG 格式还是 BMP 格式(优先保存为 PNG 格式)
- resize() 恢复为自动填充背景色(20.08 行为改为不填充，现恢复)，另新增不填充背景色的 resize_f()
- EGERGB(), EGEARGB() 等宏的返回值类型修改为 color_t
- 定时精度提升至 1ms
- 为部分类型增加 EGE_XXX_TYPEDEF 宏，控制类型定义
- 消除扩展中的头文件包含顺序依赖
- 取消 setfillstyle/getfillstyle 的弃用标记
- 图像旋转正方向修改为与坐标系一致的顺时针方向
- 调整文本垂直对齐方式的值
- 为 GCC4.5 以上版本增加弃用信息
- 线条连接点默认样式统一修改为尖角
- color_t 恢复为与 uint32_t 一致的 unsigned int 类型(20.08 改为 DWORD)

## 其它
- 绘图性能优化(GDI+ 实现的图形绘制以及 GDI 的直线绘制)
- 减少初次显示屏幕时的闪烁
- 图片读取速度优化
