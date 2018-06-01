package CommandReceivers;

import CommandControllers.CommandSQL;

public class k_receiver extends ReceiverAdapter {
    public k_receiver(CommandSQL commandSQL) {
        super(commandSQL);
    }

    @Override
    public void doAction() {
        System.out.println("cctv5\n" +
                "4");
        commandSQL.setEd(false);

    }

    @Override
    public void reverseAction() {

    }
}
