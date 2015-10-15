package body buffer is
   protected body Buffer_Acotado is
      entry Quita(Item : out Integer)
        when Nr_En_Buffer > 0 is
      begin
         Item := Buf(Primero);
         Primero := Primero +1;
         Nr_En_Buffer := Nr_En_Buffer - 1;
         Put_Line  ("Quitando del buffer");
      end;

      entry Pon(Item : in Integer)
        when Nr_En_Buffer < tamano_buffer is
      begin
         Ultimo := Ultimo + 1;
         Buf(Ultimo) := Item;
         Nr_En_Buffer := Nr_En_Buffer + 1;
         Put_Line("Poniendo en el buffer");
      end;
   end Buffer_Acotado;
end buffer;
