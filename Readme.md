## Rough Ray Tracing

纯粹基于三角面和球体的简易实现，仅opencv用于生成图片，加入了高斯滤波和中值滤波

实现结果简单粗暴，故名为Rough Ray Tracing

最终实现效果图：

![test](https://github.com/LunaElfGaming/RayTracing/raw/master/test.png)

模型导出为.obj文件格式，文件夹中test.obj为模型文件，test.mtl是对应的贴图文件，包含不同面片的颜色、高光、反射信息。

图中场景有“树”、“地面”、镜子，镜子为后方和右边竖立的两面镜子，地面无高光、有反射， 树的贴图基本都有高光。光源为两个点光源。球体为手动添加的暗红色折射物体，折射率1.2，球体中看到的是倒立的虚像，后方镜面中球体中的一条线是地面的边界线。

工程文件中init.h定义了基本的参数诸如视窗尺寸、图片像素等；Vector.h定义了向量类和基本的运算，把多数向量运算做了操作符重载；Light.h定义光源类和光线类；Triangle.h为物体类，包含场景中涉及到的平面和球面，以及求交、求法线等算法；Scene.h将所有类整合到场景中；tracer.h包含Scene类，构建光线追踪渲染算法。

完成结果进行了4次光线追踪迭代（球体折射没有算在一条光线的迭代次数中），并对最终结果做了高斯滤波和中值滤波处理来减少锯齿和噪声。

工程文件包含Opencv 3.4.1版本扩展包，结果图为test2.png。

另一个由平面、三棱锥和折射球构成的简单例子：

![test2](https://github.com/LunaElfGaming/RayTracing/raw/master/test2.png)
