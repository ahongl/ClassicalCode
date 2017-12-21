/**
*author:Li Yihong
*使用htmlunit/WebClient实现java爬虫程序，可以实现抓下css文件和js文件从而可以尽可能保留网页原有的样式和动态效果。 
*最重要的是可以实现抓取js动态加载的数据。 
*具体代码如下所示： 
*其中，webClient.getOptions().setUseInsecureSSL(true);的使用可以使程序抓取具有验证功能的网站。
*/
import java.io.IOException;

import com.gargoylesoftware.htmlunit.BrowserVersion;
import com.gargoylesoftware.htmlunit.FailingHttpStatusCodeException;
import com.gargoylesoftware.htmlunit.NicelyResynchronizingAjaxController;
import com.gargoylesoftware.htmlunit.WebClient;
import com.gargoylesoftware.htmlunit.html.HtmlPage;

public class Crawler {
    public static void main(String[] args) {

        WebClient webClient= new WebClient(BrowserVersion.CHROME);//设置浏览器  
        webClient.getOptions().setUseInsecureSSL(true);
         webClient.getOptions().setCssEnabled(true);//设置css是否生效  
         webClient.getOptions().setJavaScriptEnabled(true);//设置js是否生效  
         webClient.setAjaxController(new NicelyResynchronizingAjaxController());//设置ajax请求  
         webClient.getOptions().setTimeout(10000);  
         webClient.waitForBackgroundJavaScript(3000);  
         HtmlPage htmlPage = null;
        try {
            htmlPage = webClient.getPage("https://auction.rmfysszc.gov.cn/Result.aspx");
        } catch (FailingHttpStatusCodeException | IOException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        }//访问路径设置  
         System.out.println(htmlPage.asXml());    
         webClient.close();
         System.out.println("Success");
         System.exit(0);
    }
}
