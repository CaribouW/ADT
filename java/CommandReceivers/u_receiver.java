package CommandReceivers;

import CommandControllers.CommandClient;
import CommandControllers.CommandSQL;
import Manager.LinesManager;

import java.util.Stack;

/*
 * 仅对a c d i m t j s有效
 * */
public class u_receiver extends ReceiverAdapter {
    public u_receiver(CommandSQL commandSQL) {
        super(commandSQL);
    }

    @Override
    public void doAction() {
        if (commandSQL.getFileStack().empty()) {
            System.out.println("?");
            return;
        }
        Stack<String> fileStack = commandSQL.getFileStack();
        String commandLine = fileStack.get(fileStack.size() - 1).split("##")[0];
        CommandSQL commandSQL = getCommandSQL(commandLine);
        commandSQL.setFileStack(fileStack);
        new CommandClient(commandSQL).undoCommand();
        LinesManager editorLineManager = new LinesManager(this.commandSQL.getEditFile().getPath());
        this.commandSQL.setCurrentLine(editorLineManager.getLines().size());
    }

    private CommandSQL getCommandSQL(String commandLine) {
        CommandSQL commandSQL = new CommandSQL(commandLine, this.commandSQL.getDefaultFileName(),
                this.commandSQL.getEditFile());
        commandSQL.setCurrentLine(this.commandSQL.getCurrentLine());
        return commandSQL;
    }

    @Override
    public void reverseAction() {

    }
}
