package CommandReceivers;

import CommandControllers.CommandSQL;
import Manager.AddressAnalyser;
import Manager.LinesManager;
import Mode.Mode;

import java.util.LinkedList;
import java.util.List;

import static Manager.AddressAnalyser.listToFile;
import static Manager.AddressAnalyser.readFromConsole;

public class i_receiver extends ReceiverAdapter {
    private int currentLine;
    private LinesManager editorLineManager;
    private LinesManager consoleLineManager;

    public i_receiver(CommandSQL commandSQL) {
        super(commandSQL);
        Initialize(commandSQL);
    }

    @Override
    public void doAction() {
        readFromConsole(commandSQL);
        this.commandSQL.setMode(Mode.Command);
        this.consoleLineManager = new LinesManager(commandSQL.getConsoleFile().getPath());
        int lineIndex = getLineIndex(commandSQL, currentLine, editorLineManager);
        try {
            List<String> console = addToEditor(lineIndex);
            if (console.size() == 0)
                return;
            this.currentLine = lineIndex - 1 + console.size();
            commandSQL.setCurrentLine(currentLine);
        } catch (IndexOutOfBoundsException e) {
            System.out.println("?");
            e.printStackTrace();
        }
    }

    @Override
    public void reverseAction() {

    }

    private List<String> addToEditor(int lineIndex) throws IndexOutOfBoundsException {
        List<String> console = consoleLineManager.getLines();
        List<String> editor = editorLineManager.getLines();
        if (commandSQL.getDefaultFileName() == null) {
            listToFile(console, commandSQL.getEditFile());
            return console;
        }
        int consoleSize = console.size();
        int editorSize = editor.size();
        List<String> result = new LinkedList<>();
        for (int i = 0; i < consoleSize + editorSize; i++) {
            if (i < lineIndex - 1)
                result.add(editor.get(i));
            else if (i < lineIndex + consoleSize - 1)
                result.add(console.get(i - lineIndex + 1));
            else
                result.add(editor.get(i - consoleSize));
        }
        listToFile(result, commandSQL.getEditFile());

        return console;
    }


    private void Initialize(CommandSQL commandSQL) {
        if (commandSQL.getMode() == Mode.Input) {
            System.out.println("Mode error!");
            commandSQL.setEd(false);
        }
        commandSQL.setSaved(false);
        commandSQL.setMode(Mode.Input);
        this.editorLineManager = new LinesManager(commandSQL.getEditFile().getPath());
        this.currentLine = commandSQL.getCurrentLine();
    }

    private int getLineIndex(CommandSQL commandSQL, int currentLine, LinesManager editorLineManager
    ) {
        return AddressAnalyser.getLineIndex(commandSQL, currentLine, editorLineManager);
    }
}
