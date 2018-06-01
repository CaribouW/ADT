package CommandReceivers;

import CommandControllers.CommandSQL;

public class Big_q_receiver extends ReceiverAdapter {
    public Big_q_receiver(CommandSQL commandSQL) {
        super(commandSQL);
    }

    @Override
    public void doAction() {
        commandSQL.setEd(false);
    }

    @Override
    public void reverseAction() {
    }

}
