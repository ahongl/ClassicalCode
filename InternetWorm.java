/**
*author:Li Yihong
*本java爬虫程序在保证能爬取正常网站的同时，增加了证书伪造，针对网站反爬抓取不到数据的解决方案。
*利用java ArrayList()边抓取网站中的有效链接，边释放资源，以免因占用系统资源过多，而造成系统跑不起来而终止。经过测试，真实可用。
*/
/*
*首先，是伪造网页浏览器证书，以获取网站的信任，从而顺利地爬取到数据。具体方案如下：
*/
public static void getCertificate(){
        HostnameVerifier hv = new HostnameVerifier() {  
            public boolean verify(String urlHostName, SSLSession session) {  
                System.out.println("Warning: URL Host: " + urlHostName + " vs. "  
                                   + session.getPeerHost());  
                return true;  
            }  
        };  
        try {
            trustAllHttpsCertificates();
        } catch (Exception e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        }  
         HttpsURLConnection.setDefaultHostnameVerifier(hv);
    }
    /*
    *其中运用到的代码片段过长，已封装成函数，如下所示：
    */
    private static void trustAllHttpsCertificates() throws Exception {  
            javax.net.ssl.TrustManager[] trustAllCerts = new javax.net.ssl.TrustManager[1];  
            javax.net.ssl.TrustManager tm = new miTM();  
            trustAllCerts[0] = tm;  
            javax.net.ssl.SSLContext sc = javax.net.ssl.SSLContext  
                    .getInstance("SSL");  
            sc.init(null, trustAllCerts, null);  
            javax.net.ssl.HttpsURLConnection.setDefaultSSLSocketFactory(sc  
                    .getSocketFactory());  
        }
        /*
        *上面的程序运用到的miTM函数如下：
        */
  static class miTM implements javax.net.ssl.TrustManager,javax.net.ssl.X509TrustManager {  
        public java.security.cert.X509Certificate[] getAcceptedIssuers() {  
            return null;  
        }  

        public boolean isServerTrusted(java.security.cert.X509Certificate[] certs) {  
                return true;  
        }  

        public boolean isClientTrusted(java.security.cert.X509Certificate[] certs) {  
            return true;  
        }  

        public void checkServerTrusted(java.security.cert.X509Certificate[] certs, String authType)throws java.security.cert.CertificateException {  
            return;  
        }  

        public void checkClientTrusted(java.security.cert.X509Certificate[] certs, String authType)throws java.security.cert.CertificateException {  
            return;  
        }  
    }
    /*
    *好了，到这里的话，证书获取的代码就已经完结了。 
    *接下来就是获取网页静态页面内容的函数：
    */
    public static String returnHtml(String string){
        URL url = null; 
        try {
            url= new URL(string);
        } catch (MalformedURLException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        }
        URLConnection connection = null;
        try {
            connection = url.openConnection();
        }catch (IOException e1) {
            e1.printStackTrace();
        }
        connection.setRequestProperty("User-Agent", "Mozilla/4.0 (compatible; MSIE 5.0; Windows NT; DigExt)");
         try {
            connection.connect();
        } catch (IOException e1) {
            // TODO Auto-generated catch block
            e1.printStackTrace();
        }
         InputStreamReader isr = null;
        try {
                isr=new InputStreamReader(connection.getInputStream(),Charset.forName("UTF-8"));
            }catch (IOException e1) {
                e1.printStackTrace();
            }
        // 定义一个字符串用来存储网页内容
          String result = "";
        // 定义一个缓冲字符输入流
          BufferedReader in = null;
        // 初始化 BufferedReader输入流来读取URL的响应
           in = new BufferedReader(isr);
        // 用来临时存储抓取到的每一行的数据
           String line;
           try {
            while ((line = in.readLine()) != null) {
                // 遍历抓取到的每一行并将其存储到result里面
                result += line;
               }
        } catch (IOException e) {
            // TODO Auto-generated catch block
            System.out.println("发送GET请求出现异常！" + e);
            e.printStackTrace();
        }
        return result;
    }
    /*
    *光获取网页静态资源还是不够的，我们还要抓取页面中的链接，并进行迭代访问，以获取我们最终想要的数据：
    */
    public static void getLink(String result){
        Document doc = Jsoup.parse(result);
        Elements table = doc.select("table.resulttable");
        Elements es=table.select("a");
        for (Iterator it = es.iterator(); it.hasNext();) {
               Element e = (Element) it.next();
               link.add(e.attr("href"));
               System.out.println(e.text()+" "+e.attr("href"));
              }
    }
    /*
    *有些网站安全性方面做的比较好的话，页面的数据都采用ajax动态加载，这样的话，我们就需要获取ajax后台访问获取数据的接口，
    *然后进行链接拼接，然后直接访问后台数据接口获取json数据。具体方案如下：
    */
    public static void getJson(ArrayList<String> link){
        FileOutputStream out=null;
        try{
        out = new FileOutputStream(new File("C:\\Users\\yihong\\Desktop\\数据抓取.txt"),true);
        }catch(FileNotFoundException e){

        }
        String s;
        for(int i=0;i<link.size();i++){
            String alink=link.get(i);
            alink=alink.replaceAll("LedRM.shtml", "RMAuction.ashx");
            alink=returnHtml(alink+"&t=Sat%20Aug%2019%202017%2015:46:44%20GMT+0800%20(%E4%B8%AD%E5%9B%BD%E6%A0%87%E5%87%86%E6%97%B6%E9%97%B4)");        
            System.out.println(alink);
            ObjectMapper mapper = new ObjectMapper();  
            try {
                out.write(alink.getBytes());
            } catch (IOException e) {
                // TODO Auto-generated catch block
                e.printStackTrace();
            }
            link.remove(i);
        }
        try {
            out.close();
        } catch (IOException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        }
    }
    /*
    *最后附上主函数：
    */
    public static void main(String[] args) {
        getCertificate();
        for(int i=1;i<1513;i++){
            String result=returnHtml("https://auction.rmfysszc.gov.cn/Result.aspx?page="+i+"&size=15&name=&status=");
            System.out.println(result);
            link.clear();
            getLink(result);
            getJson(link);
        }
    }
    /*
    *static ArrayList link=new ArrayList();为全局变量，目的是为了减少资源的定义，以节省系统资源。
    *本代码均针对某一个网站进行个性化定制，如要抓取其他网站数据，仅要稍微修改代码即可。
    */
