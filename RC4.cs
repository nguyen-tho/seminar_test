using System;
using System.Text;
using System.Windows.Forms;

namespace RC4
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        public static string RC4(string input, string key)
        {
            StringBuilder result = new StringBuilder();
            int x, k, i, j, t, l;
            int[] S = new int[256];
            int[] T = new int[256];

            /* Initialization */
            for (i = 0; i < 256; i++)
            {
                S[i] = i;
                T[i] = key[i % key.Length];
            }

            // Initial Permutation of S *
            for (i = j = 0; i < 256; i++)
            {
                j = (j + S[i] + T[i]) % 256;

                // Swap(S[i], S[j])
                x = S[i];
                S[i] = S[j];
                S[j] = x;
            }

            // Stream Generation 
            for (l = j = 0; l < input.Length; l++)
            {
                i = l % 256;
                j = (j + S[i]) % 256;

                // Swap(S[i], S[j])
                x = S[i];
                S[i] = S[j];
                S[j] = x;

                t = (S[i] + S[j]) % 256;
                k = S[t];
                result.Append((char)(input[l] ^ k));
            }
            return result.ToString();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            txtEncrypt.Text = RC4(txtInput.Text, txtKey.Text);
        }

        private void button2_Click(object sender, EventArgs e)
        {
            txtDecrypt.Text = RC4(txtEncrypt.Text, txtKey.Text);
        }

        private void Form1_Load(object sender, EventArgs e)
        {

        }
    }
}