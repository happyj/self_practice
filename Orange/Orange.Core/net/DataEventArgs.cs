using System;
using System.Collections.Generic;
using System.Text;

namespace Orange.Core.net
{
    public class CDataEventArgs : EventArgs
    {
        public static CDataEventArgs<TArg1> Create<TArg1>(TArg1 arg1)
        {
            return new CDataEventArgs<TArg1>(arg1);
        }

        public static CDataEventArgs<TArg1, TArg2> Create<TArg1, TArg2>(TArg1 arg1, TArg2 arg2)
        {
            return new CDataEventArgs<TArg1, TArg2>(arg1, arg2);
        }
    }


    public class CDataEventArgs<TArg1> : EventArgs
    {
        public TArg1 Arg1
        {
            get;
            set;
        }

        public CDataEventArgs(TArg1 arg1)
        {
            Init(arg1);
        }

        public void Init(TArg1 arg1)
        {
            Arg1 = arg1;
        }

        public void Destroy()
        {
            Arg1 = default(TArg1);
        }
    }

    public class CDataEventArgs<TArg1, TArg2> : EventArgs
    {
        public TArg1 Arg1
        {
            get;
            set;
        }
        public TArg2 Arg2
        {
            get;
            set;
        }

        public CDataEventArgs(TArg1 arg1, TArg2 arg2)
        {
            Init(arg1, arg2);
        }

        public void Init(TArg1 arg1, TArg2 arg2)
        {
            Arg1 = arg1;
            Arg2 = arg2;
        }
        public void Destroy()
        {
            Arg1 = default(TArg1);
            Arg2 = default(TArg2);
        }
    }
}
