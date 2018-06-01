package edLineEditor;

import Manager.ConsoleManager;

import java.io.IOException;

/*
 *
 * Log::
 *
 * 	5.15:初步看题，确定流程与基本需求
 *
 * 	5.22:实现几个简单的类，EL迫在眉睫，无力顾及大作业orz
 *
 *  5.23:命令模式design pattern 用于撤销操作，将一个请求封装成一个对象，从而可以用不同的请求对客户进行参数化
 *       定义三个角色：1、receiver 真正的命令执行对象 2、Command 3、invoker 使用命令对象的入口
 *       已实现基本框架，之后再一次性把所有receivers完成即可
 *       原有代码暂时不删
 *       待实现的功能：每个receiver，撤销操作undo留到最后，届时往switch里加栈、map，来处理多次撤销和标记操作
 *  5.25:EL结束，这周末绝对不碰代码
 *  5.30:已实现 a c i p = q Q
 *  5.31：ac 98
 *      六一之前是完不成了，还差两个高级指令的实现
 *  6.1：早9点，AC for all...
 *       终于可以安心写文档了
 *
 * */

/**
 * 程序说明：
 * <p>
 * The entry of the programme:ConsoleManager.
 *
 */

public class EDLineEditor {
    public static ConsoleManager consoleManager = new ConsoleManager();

    /**
     * 接收用户控制台的输入，解析命令，根据命令参数做出相应处理。
     * 不需要任何提示输入，不要输出任何额外的内容。
     * 输出换行时，使用System.out.println()。或者换行符使用System.getProperty("line.separator")。
     * <p>
     * 待测方法为public static void main(String[] args)方法。args不传递参数，所有输入通过命令行进行。
     * 方便手动运行。
     * <p>
     * 说明：可以添加其他类和方法，但不要删除该文件，改动该方法名和参数，不要改动该文件包名和类名
     */
    public static void main(String[] args) {
        consoleManager.startLineOperation();
        if (consoleManager.isEd()) {
            consoleManager.consoleReadOn();
        }
    }
}
