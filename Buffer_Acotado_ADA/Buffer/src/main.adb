with buffer;  use buffer;

procedure Main is
   Variable: aliased Buffer_Acotado;
   type punteroBuffer is access all Buffer_Acotado;
   numeroAfuera : Integer;
      task type Poner(Puntero: punteroBuffer);
   task body Poner is begin
      for i in 1..50 loop
         Puntero.Pon(i);
      end loop;
   end;

      task type Quitar(Puntero: punteroBuffer);
   task body Quitar is begin
      for i in 1..50 loop
          Puntero.Quita(numeroAfuera);
      end loop;
   end;

   tamano_buffer : constant Integer := 10;
   type IndexBuff is mod tamano_buffer;
   type BufferIn is array (IndexBuff) of Poner(Variable'Access);
   type BufferOut is array(IndexBuff) of Quitar(Variable'Access);

   arregloIn : BufferIn;
   arregloOut: BufferOut;

begin
   --  Insert code here.
   null;
end Main;
