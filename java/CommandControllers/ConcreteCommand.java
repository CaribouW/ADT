package CommandControllers;

import CommandReceivers.Receiver;

public class ConcreteCommand implements Command {
    private Receiver receiver;

    public ConcreteCommand(Receiver receiver) {
        this.receiver = receiver;
    }

    @Override
    public void execute() {
        receiver.doAction();
    }

    @Override
    public void undo() {
        receiver.reverseAction();
    }
}