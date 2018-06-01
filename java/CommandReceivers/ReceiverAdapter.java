package CommandReceivers;

import CommandControllers.CommandSQL;

public class ReceiverAdapter implements Receiver {
    protected CommandSQL commandSQL;

    protected ReceiverAdapter(CommandSQL commandSQL) {
        this.commandSQL = commandSQL;
    }

    @Override
    public void doAction() {
        System.out.println(this.commandSQL.getMiddleParam());

    }

    @Override
    public void reverseAction() {

    }
}
