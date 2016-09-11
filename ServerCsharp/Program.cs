using System;
using System.Collections.Generic;
using System.IO;
using System.IO.MemoryMappedFiles;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Google.Protobuf;
using Google.Protobuf.Examples.AddressBook;
using static Google.Protobuf.Examples.AddressBook.Person.Types;


namespace ServerCsharp
{
    class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine("WRITER C#");
            Console.WriteLine("Memory-Mapped file example. Press any key to write new data, Esc to exit");

            // creating not-persistent, pagefile-based memory-mapped file
            using (MemoryMappedFile mmf = MemoryMappedFile.CreateNew("comunicationInstructor-Simbox", 10000))
            {
                ConsoleKeyInfo keyInfo;
                do
                {
                    // opening the stream to write to the file
                    using (MemoryMappedViewStream stream = mmf.CreateViewStream())
                    {
                        // Write something to the shared memory
                        BinaryWriter writer = new BinaryWriter(stream); // use only BinaryWriter here!

                        Person john = new Person
                        {
                            Id = 1234,
                            Name = "John Doe",
                            Email = "jdoe@example.com",
                            Phones = { new PhoneNumber { Number = "555-4321", Type = PhoneType.Home } }
                        };

                        AddressBook myaddress = new AddressBook();
                        myaddress.People.Add(john);

                        Byte[] msg = myaddress.ToByteArray();

                        writer.Write(msg);


                        //writer.Write("This is our large data block Cierto.");
                        //writer.Write(DateTime.Now.ToLongTimeString());
                        //Console.WriteLine("New data saved to MMF: " + DateTime.Now.ToLongTimeString());
                    }
                    keyInfo = Console.ReadKey();
                } while (keyInfo.Key != ConsoleKey.Escape);
            } // closing and releasing the file
        }
    }
}
