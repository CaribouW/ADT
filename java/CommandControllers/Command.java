package CommandControllers;

/**
 * Command design pattern---
 * Command interface:Command
 * ConcreteCommand: ConcreteCommand
 * CommandInvoker:CommandSQL
 * Receiver:All of the classes that implement Receiver interface.
 *
 *
 * CommandInvoker invoker = new CommandInvoker();
 Receiver receiver = new ConcreteReceiver1();

 Command command = new ConcreteCommand1(receiver);
 invoker.setCommand(command);
 invoker.action();
 * @author lfm
 * @time 5.23
 */
public interface Command {
    //执行方法
    void execute();

    //撤销方法
    void undo();
}

