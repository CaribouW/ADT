package Splitter;

import java.util.ArrayList;
import java.util.List;

/**
 * Split and analyse the address after the CommandSplitter
 * Split the address clearer
 *
 * @author lfm
 * @time 5.22
 */
public class AddressSplitter {
    private String address;
    private String middleCommand;
    private List<String> addressList = new ArrayList<>();

    public AddressSplitter(CommandSplitter commandSplitter) {
        this.middleCommand = commandSplitter.getMiddleCommand();
        this.address = commandSplitter.getAddress();
    }

    public void doAddressSplit() {
        int len = address.length();
        /*
         * 地址位为空或者仅含一个
         * */
        if (address.equals("") || address.length() == 1) {
            addressList.add(address);
            return;
        }
        /*
         * 对于特殊情况/ / 和 ?  ?
         * */
        String[] tmp1 = address.split("[?]");
        String[] tmp2 = address.split("[/]");
        if (tmp1.length > 1 || tmp2.length > 1) {
            //列表头用于判定/和? ，便于后续操作
            addressList.add(String.valueOf(address.charAt(0)));
            addressList.add(address.substring(1, len - 1));
            return;
        } else {
            for (int index = 0; index < len; index++)
                addressList.add(String.valueOf(address.charAt(index)));
            return;
        }
    }

    public List<String> getAddressList() {
        return addressList;
    }

    public static void main(String[] args) {
        CommandSplitter commandSplitter = new CommandSplitter(".33a");
        commandSplitter.doSplitCommand();
        AddressSplitter addressSplitter=new AddressSplitter(commandSplitter);
        addressSplitter.doAddressSplit();
        System.out.println(addressSplitter.addressList);
    }
}
