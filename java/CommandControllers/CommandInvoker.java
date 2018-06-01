package CommandControllers;

/**
 * Invoke the command
 *
 * @author lfm
 * @time 5.23
 */
public class CommandInvoker {
    private Command command;

    public void setCommand(Command command) {
        this.command = command;
    }

    public void doAction() {
        this.command.execute();
    }

    public void undo() {
        this.command.undo();
    }
}
