using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Data.SQLite;
using System.Data.Common;
using System.IO;
using System.Xml;

namespace app_db_make
{
    public partial class game_db_make_main : Form
    {
        static string[] fields = new string[] 
        { 
            "id", "name_cn", "name_en", "name_other", "language", 
            "release_date" ,"category" ,"company","platform","version", "icon",
            "homepage", "rank","url","torrent","magnet","baiduyun", 

            //extra detailed information 
            "size",
            "star_marks", 
            "desc",
            "license",
            "update_time",
            //5 snapshots
            "snapshot_urls"
        };
 
        public game_db_make_main()
        {
            InitializeComponent(); 

            tbox_icon_name.DragDrop += tbox_DragDrop;
            tbox_icon_name.DragEnter += tbox_DragEnter;
            tbox_torrent.DragDrop += tbox_DragDrop;
            tbox_torrent.DragEnter += tbox_DragEnter;
 
            btn_add.MouseClick += btn_add_MouseClick;

            cbox_category.SelectedIndex = 0;
            cbox_language.SelectedIndex = 0;
            cbox_license.SelectedIndex = 0;
            cbox_star_marks.SelectedIndex = 0;

            //MainItem item = new MainItem("EEEDA1AFA8B14A01B21286D786D247B6.xml");
        }

        void tbox_DragEnter(object sender, DragEventArgs e)
        {
            if (e.Data.GetDataPresent(DataFormats.FileDrop))
                e.Effect = DragDropEffects.Link;
            else e.Effect = DragDropEffects.None; 
        }

        void tbox_DragDrop(object sender, DragEventArgs e)
        {
            var _filepath = ((System.Array)e.Data.GetData(DataFormats.FileDrop)).GetValue(0).ToString();
            var _filename = _filepath.Substring(_filepath.LastIndexOf("\\") + 1);

            TextBox tbox = (sender as TextBox);
            tbox.Text = _filepath;  
        }

        private string GetBase64String(System.Drawing.Image image)
        {
            System.IO.MemoryStream ms = new System.IO.MemoryStream();

            image.Save(ms, System.Drawing.Imaging.ImageFormat.Jpeg);
            byte[] buffer = ms.ToArray();

            return Convert.ToBase64String(buffer);
        }
        private string FixBase64ForImage(string ImageText)
        {
            System.Text.StringBuilder sbText = new System.Text.StringBuilder(ImageText, ImageText.Length);
            sbText.Replace("/r/n", String.Empty);
            sbText.Replace(" ", String.Empty);
            return sbText.ToString();
        }

        private Image GetImageFromBase64String(string ImageText)
        {
            if (ImageText.Length > 0)
            {
                Byte[] bitmapData = new Byte[ImageText.Length];

                //bitmapData = Convert.FromBase64String(FixBase64ForImage(ImageText));
                bitmapData = Convert.FromBase64String(ImageText);
                System.IO.MemoryStream streamBitmap = new System.IO.MemoryStream(bitmapData);
                //Bitmap bitImage = new Bitmap((Bitmap)Image.FromStream(streamBitmap));
                return Image.FromStream(streamBitmap);
            }
            else
            {
                return null;
            }
        }

        void Clear()
        {
            tbox_name_cn.Text = "";
            tbox_name_en.Text = "";
            tbox_name_other.Text = "";
            tbox_version.Text = "";
            tbox_icon_name.Text = "";
            tbox_homepage.Text = "";
            tbox_torrent.Text = "";
            tbox_release_date.Text = "";
            tbox_rank.Text = "";
            tbox_baiduyun.Text = "";
            tbox_company.Text = "";
            tbox_desc.Text = "";
            cbox_category.SelectedIndex = 0;
            cbox_language.SelectedIndex = 0;
            cbox_license.SelectedIndex = 0;
            cbox_star_marks.SelectedIndex = 0;
        }

        void AddToAppstore()
        {
            string dbName = string.Format("{0}.db", "main");//Guid.NewGuid().ToString("N").ToUpper());
            SQLiteConnection connection = new SQLiteConnection();
            SQLiteConnectionStringBuilder str = new SQLiteConnectionStringBuilder();
            str.DataSource = dbName;

            connection.ConnectionString = str.ToString();
            connection.Open();
            
            string createStatement = @"create table if not exists onestore_game(" +
                "[id] GUID PRIMARY KEY, " +
                "[name_cn] NVARCHAR, " +
                "[name_en] NVARCHAR, " +
                "[name_other] NVARCHAR, " +
                "[language] NVARCHAR, "+
                "[release_date] NVARCHAR, " +
                "[category] NVARCHAR,"+
                "[company] NVARCHAR,"+
                "[platform] NVARCHAR,"+
                "[version] NVARCHAR, " +
                "[icon] BLOB, " +
                "[homepage] NVARCHAR, " +
                "[rank] INT,"+
                "[url] NVARCHAR,"+
                "[torrent] BLOB,"+
                "[magnet] NVARCHAR,"+
                "[baiduyun] NVARCHAR,"+
                "[size] NVARCHAR,"+
                "[star_marks] INT,"+
                "[desc] NVARCHAR,"+
                "[license] NVARCHAR,"+
                "[update_time] NVARCHAR,"+
                "[snapshot_urls] NVARCHAR);";
 
            DbTransaction transaction = connection.BeginTransaction(); 

            SQLiteCommand command = new SQLiteCommand();
            command.CommandText = createStatement;
            command.Connection = connection;
            command.ExecuteNonQuery();

            for(int i=0;i<1000;++i)
            { 
                var item = GetItem();
                if (item == null)
                    return;

                if (i == 0)
                {
                    item.Save(); 
                }

                string fieldstr = "";
                foreach (var field in fields)
                {
                    fieldstr += field + ",";
                }

                fieldstr = fieldstr.Substring(0, fieldstr.Length - 1);

                string paramstr = "";
                foreach (var field in fields)
                {
                    paramstr += "@" + field + ",";
                }

                paramstr = paramstr.Substring(0, paramstr.Length - 1);

                string insertStatement = string.Format(@"insert into onestore_game({0}) values({1})", fieldstr, paramstr);
                command.CommandText = insertStatement;
                int idx = 0;
                foreach (var field in fields)
                {
                    command.Parameters.Add(new SQLiteParameter("@" + field, item.GetFieldByIndex(idx++)));
                }

                var ret = command.ExecuteNonQuery();
            }

            transaction.Commit();

            connection.Close(); 

            Clear();
        }

        void AddToGameStore()
        {

        }

        void btn_add_MouseClick(object sender, MouseEventArgs e)
        {
            AddToAppstore();
        }

        byte[] readBytesFromFile(string filepath)
        {
            FileStream fs = new FileStream(filepath, FileMode.Open);
            byte[] buffer = (byte[])(StreamUtil.ReadFully(fs).Clone());
            fs.Close();
            return buffer;
        }

        MainItem GetItem()
        {
            MainItem item = new MainItem();
            
            item.name_cn = tbox_name_cn.Text; if (item.name_cn == null || item.name_cn.Trim() == "") return null;
            item.name_en = tbox_name_en.Text; 
            item.name_other = tbox_name_other.Text;
            item.release_date = tbox_release_date.Text;
            item.version = tbox_version.Text;

            var torrentPath = tbox_torrent.Text; 
            if(torrentPath!=null &&torrentPath.Trim()!="")
            {
                item.torrent = readBytesFromFile(torrentPath);
            } 

            var iconPath = tbox_icon_name.Text;
            if (iconPath == null || iconPath.Trim() == "") return null; 
            item.icon = readBytesFromFile(iconPath); 
            item.homepage = tbox_homepage.Text;

            if(tbox_rank.Text!=null &&tbox_rank.Text.Trim()!="")
            {
                item.rank = int.Parse(tbox_rank.Text); 
            }

            item.baiduyun = tbox_baiduyun.Text;
            item.category = cbox_category.SelectedItem.ToString();
            item.company = tbox_company.Text;
            item.desc = tbox_desc.Text;
            item.language = cbox_language.SelectedItem.ToString();
            item.license = cbox_license.SelectedItem.ToString();
            item.magnet = tbox_magnet.Text;
            item.size = tbox_size.Text;
            item.star_marks = int.Parse(cbox_star_marks.SelectedItem.ToString());
            item.update_time = tbox_update_time.Text;
            item.url = tbox_url.Text;
            item.snapshot_urls = tbox_snapshots.Text;

            return item; 
        }

        public class MainItem
        {
            Dictionary<int, object> values = null;

            private Guid __id = Guid.NewGuid();         public Guid     id      { get{return __id;} set{__id = value;values[0] = value;} }
            private string __name_cn = "";              public string   name_cn { set { __name_cn = value; values[1] = value; } get { return __name_cn; } }
            private string __name_en = "";              public string   name_en { set { __name_en = value; values[2] = value; } get { return __name_en; } }
            private string __name_other = "";           public string   name_other { set { __name_other = value; values[3] = value; } get { return __name_other; } }
            private string __language = "";             public string   language { set { __language = value; values[4] = value; } get { return __language; } }
            private string __release_date = "";         public string   release_date { set { __release_date = value; values[5] = value; } get { return __release_date; } }
            private string __category = "";             public string   category { set { __category = value; values[6] = value; } get { return __category; } }
            private string __company = "";              public string company { set { __company = value; values[7] = value; } get { return __company; } }
            private string __platform = "";             public string   platform { set { __platform = value; values[8] = value; } get { return __platform; } }
            private string __version = "";              public string   version { set { __version = value; values[9] = value; } get { return __version; } }
            private byte[] __icon = null;               public byte[]   icon    { set { __icon = value; values[10] = value; } get { return __icon; } }
            private string __homepage = "";             public string   homepage { set { __homepage = value; values[11] = value; } get { return __homepage; } }
            private string __url = "";                  public string   url     { set { __url = value; values[12] = value; } get { return __url; } }
            private int __rank = 0;                     public int      rank    { set { __rank = value; values[13] = value; } get { return __rank; } }
            private byte[] __torrent = null;            public byte[]   torrent { set { __torrent = value; values[14] = value; } get { return __torrent; } }
            private string __magnet = "";               public string   magnet  { set { __magnet = value; values[15] = value; } get { return __magnet; } }
            private string __baiduyun = "";             public string   baiduyun { set { __baiduyun = value; values[16] = value; } get { return __baiduyun; } }
            private string __size = "";                 public string   size    { set { __size = value; values[17] = value; } get { return __size; } }
            private int __star_marks = 0;               public int   star_marks { set { __star_marks = value; values[18] = value; } get { return __star_marks; } }
            private string __desc = "";                 public string   desc    {set { __desc = value ; values[19] = value;} get { return __desc; }}
            private string __license = "";              public string   license { set { __license = value; values[20] = value; } get { return __license; } }
            private string __update_time = "";          public string update_time { set { __update_time = value; values[21] = value; } get { return __update_time; } }
            private string __snapshot_urls = "";        public string   snapshot_urls{ set{ __snapshot_urls = value; values[22] = value; } get { return __snapshot_urls;}}
 
            public void SetFieldByIndex(int index,object value)
            {
                values[index] = value;
            }

            public object GetFieldByIndex(int index)
            {
                 return values[index];
            }

            public MainItem()
            {
                values = new Dictionary<int, object>(); 

                values.Add(0, id);
                values.Add(1, name_cn);
                values.Add(2, name_en);
                values.Add(3, name_other);
                values.Add(4, language);
                values.Add(5, release_date);
                values.Add(6, category);
                values.Add(7, company);
                values.Add(8, platform);
                values.Add(9, version);
                values.Add(10, icon);
                values.Add(11, homepage);
                values.Add(12, url);
                values.Add(13, rank);
                values.Add(14, torrent);
                values.Add(15, magnet);
                values.Add(16, baiduyun);
                values.Add(17, size);
                values.Add(18, star_marks);
                values.Add(19, desc);
                values.Add(20, license);
                values.Add(21, update_time);
                values.Add(22, snapshot_urls);
            }

            public MainItem(string xmlPath)
                :this()
            {
                XmlReaderSettings settings = new XmlReaderSettings();
                 
                XmlReader xmlReader = XmlReader.Create(xmlPath, settings); 
                 
                for(;xmlReader.Read();)
                {
                    switch(xmlReader.NodeType)
                    {
                        case XmlNodeType.Element:
                        {
                             if(!xmlReader.IsEmptyElement)
                             {
                                 Console.Write(xmlReader.Name);
                             }
                        }
                        break;
                        case XmlNodeType.Text:
                        {
                            Console.WriteLine(xmlReader.Value);
                        }
                        break;
                    }
                }

                xmlReader.Close();
            }

            public void Save()
            {
                using (MemoryStream ms = new MemoryStream())
                {
                    XmlWriterSettings settings = new XmlWriterSettings();
                    settings.Indent = true;
                    //注意如果不设置encoding默认将输出utf-16 
                    //注意这儿不能直接用Encoding.UTF8如果用Encoding.UTF8将在输出文本的最前面添加4个字节的非xml内容 
                    settings.Encoding = new UTF8Encoding(false);

                    settings.NewLineChars = Environment.NewLine;

                    using (XmlWriter xmlWriter = XmlWriter.Create(ms, settings))
                    {  
                        xmlWriter.WriteStartDocument(false);
                        {    
                            xmlWriter.WriteStartElement("box");
                            { 
                                xmlWriter.WriteElementString("id",id.ToString("N").ToUpper());
                                xmlWriter.WriteElementString("name_cn",name_cn);
                                xmlWriter.WriteElementString("name_en",name_en);
                                xmlWriter.WriteElementString("name_other",name_other);
                                xmlWriter.WriteElementString("language",language);
                                xmlWriter.WriteElementString("release_date",release_date);
                                xmlWriter.WriteElementString("category",category);
                                xmlWriter.WriteElementString("company", company);
                                xmlWriter.WriteElementString("platform",platform);
                                xmlWriter.WriteElementString("version",version);
                                xmlWriter.WriteStartElement("icon");
                                    xmlWriter.WriteBase64(icon,0,icon.Count());//.WriteElementString("icon",icon);
                                xmlWriter.WriteEndElement();
                                xmlWriter.WriteElementString("homepage",homepage);
                                xmlWriter.WriteElementString("url",url);
                                xmlWriter.WriteElementString("rank",rank.ToString());
                                if(torrent!=null)
                                {
                                    xmlWriter.WriteStartElement("torrent");
                                    xmlWriter.WriteBase64(torrent,0,torrent.Count());
                                    xmlWriter.WriteEndElement();
                                } 
                                xmlWriter.WriteElementString("magnet",magnet);
                                xmlWriter.WriteElementString("baiduyun",baiduyun);
                                xmlWriter.WriteElementString("size",size);
                                xmlWriter.WriteElementString("star_marks",star_marks.ToString());
                                 xmlWriter.WriteElementString("desc",desc);
                                 xmlWriter.WriteElementString("license",license);
                                 xmlWriter.WriteElementString("update_date",update_time);
                                 xmlWriter.WriteElementString("snapshot_urls",snapshot_urls);   
                            }
                            xmlWriter.WriteEndElement();
                        }
                        xmlWriter.WriteEndDocument();

                    } 

                    string xml = Encoding.UTF8.GetString(ms.ToArray());

                    File.WriteAllText(id.ToString("N").ToUpper()+".xml", xml); 
                }
            }
        } 
    }
}
