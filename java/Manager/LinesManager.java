package Manager;

import org.junit.Assert;

import java.io.*;
import java.util.LinkedList;
import java.util.List;

/**
 * Deal with all the line operations in the commands.
 * We just let the lines be one list "lines"
 *
 * @author lfm
 * @time 5.22
 */
public class LinesManager {
    private File targetFile;
    private List<String> lines = new LinkedList<>();
    private int lineSize = lines.size();
    //行计数器默认为最后一行
    //From 1 to lineSize
    private int currentLine = lineSize;

    public LinesManager(String targetFilePath) {
        targetFile = new File(targetFilePath);
    }

    /**
     * Get the Target index of the string
     *
     * @param index:Form[0] to [lineSize-1]
     * @return return the str; return null if the operation would cause one exception.
     */
    public String getStringOfEditor(int index) {
        try {
            return lines.get(index);
        } catch (IndexOutOfBoundsException e) {
            return null;
        }
    }

    public String getFirstLine() {
        return lines.get(0);
    }

    public String getLastLine() {

        return lines.get(lineSize - 1);
    }

    /**
     * 删除指定行
     * 如果被删除的文本后还有文本行，则当前行被设为该行
     * 否则设为被删除的文本的上一行。
     *
     * @param index:From [0] to [lineSize-1]
     */
    public void deleteLine(int index) {
        if (index == this.lineSize - 1) {
            this.currentLine = this.lineSize - 1;
        }
        lines.remove(index);
        this.lineSize = lines.size();
    }

    public int getCurrentLine() {
        flushList();
        return currentLine;
    }

    /**
     * Change the current line.
     * <p>
     * Notice to consider the "?" condition
     *
     * @param off :True then we move form the current condition.
     *            False then we reset it.
     */
    public void setCurrentLine(int offset, boolean off) {
        if (!off)
            this.currentLine = offset;
        else
            this.currentLine += offset;
    }

    public List<String> getLines() {
        flushList();
        return lines;
    }

    private void flushList() {
        try {
            BufferedReader bufferedReader = new BufferedReader(new FileReader(this.targetFile));
            String tmp;
            lines = new LinkedList<>();
            while ((tmp = bufferedReader.readLine()) != null) {
                lines.add(tmp);
            }
            this.lineSize = lines.size();
            this.currentLine = lineSize;
            bufferedReader.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

}
