package CommandReceivers;

import CommandControllers.CommandSQL;

import java.util.List;

public class f_receiver extends ReceiverAdapter {
    private String defaultName;

    public f_receiver(CommandSQL commandSQL) {
        super(commandSQL);
        Initialize(commandSQL);
    }

    @Override
    public void doAction() {
        List<String> rearList = commandSQL.getRearList();
        try {
            if (rearList.get(0).equals("")) {
                if (defaultName == null)
                    throw new NullPointerException();
                System.out.println(defaultName);
            } else {
                this.defaultName = rearList.get(0);
                commandSQL.setDefaultFileName(defaultName);
            }
        } catch (NullPointerException e) {
            System.out.println("?");
        }
    }

    @Override
    public void reverseAction() {

    }

    private void Initialize(CommandSQL commandSQL) {
        this.defaultName = commandSQL.getDefaultFileName();
    }
}
