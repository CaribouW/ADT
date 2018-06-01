package CommandControllers;

import CommandReceivers.*;
import Manager.ConsoleManager;

/**
 * Conduct the command
 *
 * @author lfm
 * @time 5.23
 */
public class CommandClient {
    private CommandSQL commandSQL;
    private char middleCommand;
    private Receiver receiver;

    public CommandClient(CommandSQL commandSQL) {
        this.commandSQL = commandSQL;
        this.middleCommand = commandSQL.getMiddleParam();
    }

    /**
     * Without the undo command.
     * Conduct the normal command and use the command pattern to implement.
     */
    public void doCommand() {
        commandSQL.setUndo(false);
        ConsoleManager.IsUndo = false;
        CommandInvoker commandInvoker = new CommandInvoker();
        this.receiver = commandSwitcher(this.middleCommand);
        Command command = new ConcreteCommand(receiver);
        commandInvoker.setCommand(command);
        commandInvoker.doAction();
    }

    /**
     * Conduct the command with the undo mode, which means we don't have to
     * push the command info into the stack.
     */
    public void undoCommand() {
        commandSQL.setUndo(true);
        ConsoleManager.IsUndo = true;
        CommandInvoker commandInvoker = new CommandInvoker();
        this.receiver = commandSwitcher(this.middleCommand);
        Command command = new ConcreteCommand(receiver);
        commandInvoker.setCommand(command);
        commandInvoker.undo();
    }

    /**
     * A huge switch method.
     * scan the middleCommand, and we could determine which command we
     * are going to do.
     *
     * @param middleCommand:The middle command,which contains all of the command types.
     * @return The target command receiver.
     */
    private Receiver commandSwitcher(char middleCommand) {
        switch (middleCommand) {
            case 'a':
                return new a_Receiver(commandSQL);
            case 'i':
                return new i_receiver(commandSQL);
            case 'c':
                return new c_receiver(commandSQL);
            case 'd':
                return new d_receiver(commandSQL);
            case 'p':
                return new p_receiver(commandSQL);
            case '=':
                return new equal_receiver(commandSQL);
            case 'q':
                return new small_q_receiver(commandSQL);
            case 'Q':
                return new Big_q_receiver(commandSQL);
            case 'z':
                return new z_receiver(commandSQL);
            case 'f':
                return new f_receiver(commandSQL);
            case 'w':
                return new Small_w_receiver(commandSQL);
            case 'W':
                return new Big_w_receiver(commandSQL);
            case 'm':
                return new m_receiver(commandSQL);
            case 't':
                return new t_receiver(commandSQL);
            case 'j':
                return new j_receiver(commandSQL);
            case 's':
                return new s_receiver(commandSQL);
            case 'k':
                return new k_receiver(commandSQL);
            case 'u':
                return new u_receiver(commandSQL);
            default:
                break;
        }
        return null;
    }
}
