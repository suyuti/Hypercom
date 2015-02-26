using System;
using System.Collections.Generic;
using System.Text;

namespace MonitorBussiness
{
    class Common
    {
        public static byte[] ToByteArray(int number, int arraySize)
        {
            byte[] intByte = new byte[arraySize];
            for (int i = 0; i < arraySize; i++)// 4 max pt ca e int 32 biti 
            {
                intByte[i] = (byte)(number >> (8 * i));
            }
            return intByte;
        }

        public static int ToInt(byte[] intByte, int byteArraySize)
        {
            int fromByte = 0;
            for (int i = 0; i < byteArraySize; i++)
            {
                int n = (intByte[i] < 0 ? (int)intByte[i] + 256 : (int)intByte[i]) << (8 * i);
                fromByte += n;
            }
            return fromByte;
        }
    }
}
