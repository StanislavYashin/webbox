using System;
using System.Collections.Generic;
using System.Linq;
using System.Windows.Forms;

namespace app_db_make
{
    static class Program
    {
        /// <summary>
        /// 应用程序的主入口点。
        /// </summary>
        [STAThread]
        static void Main()
        {
            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);
            Application.Run(new app_db_make_main());
        }
    }
}
