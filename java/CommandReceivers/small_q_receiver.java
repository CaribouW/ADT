package CommandReceivers;

import CommandControllers.CommandSQL;
import Manager.ConsoleManager;

import java.io.BufferedReader;
import java.io.IOException;

public class small_q_receiver extends ReceiverAdapter {
    public small_q_receiver(CommandSQL commandSQL) {
        super(commandSQL);
    }

    @Override
    public void doAction() {
        if (!this.commandSQL.isSaved()) {
            System.out.println("?");
            String nextLine = getNextConsoleLine();
            if (nextLine != null && nextLine.equals("q")) {
                this.commandSQL.setEd(false);
            }
        } else {
            this.commandSQL.setEd(false);
        }
    }

    @Override
    public void reverseAction() {

    }

    /**
     * @return The next line in the console
     */

    private String getNextConsoleLine() {
        BufferedReader bufferedReader = ConsoleManager.bufferedReader;
        try {
            return bufferedReader.readLine();
        } catch (IOException e) {
            e.printStackTrace();
        }
        return "";
    }
}
