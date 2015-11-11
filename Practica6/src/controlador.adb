package body controlador is
   protected body ObjetoControlador is
      entry Wait when Call_Count > 0 is
      begin
         Call_Count := Call_Count - 1;
      end Wait;

      procedure Handle is
      begin
         Call_Count := Call_Count + 1;
      end Handle;

   end ObjetoControlador;
end controlador;
