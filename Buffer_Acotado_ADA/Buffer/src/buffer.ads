with GNAT.IO;  use GNAT.IO;
package buffer is
   tamano_buffer : constant Integer := 8;
   type Index is mod tamano_buffer;
   subtype Cuenta is Natural range 0 .. tamano_buffer;
   type Buffer is array (Index) of Integer;

   protected type Buffer_Acotado is
      entry Quita(Item : out Integer);
      entry Pon(Item : in Integer);
   private
      Primero : Index := Index'First;
      Ultimo : Index := Index'First;
      Nr_En_Buffer : Cuenta := 0;
      Buf : Buffer;
   end;
end buffer;
