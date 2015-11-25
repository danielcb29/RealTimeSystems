pragma Task_Dispatching_Policy(FIFO_Within_Priorities);
with GNAT.IO;  use GNAT.IO;
with Ada.Real_Time; use Ada.Real_Time;
with System; use System;
procedure Main is

   type InstanteCritico is access all Time;
   Ti: Time;
   Tf: Time;
   dif: Time_Span;
   TCritico : aliased Time;

   type marco_t is record
      id,prioridad,c : Integer;
      t : Time_Span;
      ic : Time;
   end record;

   type MarcoTemporal is access all marco_t;

   procedure spin_m(p: integer) is
      C_1MS:constant integer:= 160000; -- Machine dependent
      DIM: constant integer:= 100;
      limit:integer;
      a: array (0..DIM-1) of integer;
   begin
      limit := C_1MS * p -1;
      for i in 0..limit loop
         a(i mod DIM) := i;
      end loop;
   end;

   task type mostrar_tiempos(inc: InstanteCritico) is
      pragma Priority(Priority'Last);
   end;
   task body mostrar_tiempos is
      n : Time;
      int : Time_Span;
   begin
      delay until inc.all;
      n:= inc.all;
      for i in 0..199 loop
         put_line("**********************"&Integer'Image(i*10) & "ms*****************");
         int := Milliseconds(10);
         n:= n + int;
         delay until n;
      end loop;

   end;

   type tareaMostrar is access mostrar_tiempos;
   objMostrar : tareaMostrar;

   task type funcion_hebra(mt:MarcoTemporal) is
      pragma Priority(mt.all.prioridad);
   end;
   task body funcion_hebra is
      n : Time;
   begin
      delay until mt.all.ic;
      n:= mt.all.ic;
      while true loop
         put_line("Hilo id: "&Integer'Image(mt.all.id)&" con prioridad: "&Integer'Image(mt.all.prioridad)&" inicia la accion periodica");
         spin_m(mt.all.c);
         put_line("Hilo id: "&Integer'Image(mt.all.id)&" termina la accion periodica");
         n:= n + mt.all.t;
         delay until n;
      end loop;

   end;

   type tareaFuncionHebra is access funcion_hebra;
   primerHilo : tareaFuncionHebra;
   segundoHilo : tareaFuncionHebra;
   tercerHilo : tareaFuncionHebra;

   marcoUno : aliased marco_t;
   marcoDos:aliased  marco_t;
   marcoTres: aliased marco_t;



begin
   Ti:=clock;
   spin_m(1000);
   Tf:=clock;
   dif:=Tf-Ti;
   put_line(duration'image(To_Duration(dif)));

   TCritico:= clock + Milliseconds(1000);

      objMostrar:= new mostrar_tiempos(TCritico'Access);

      marcoUno.id := 1;
      marcoUno.c := 100;
      marcoUno.prioridad := 3;
      marcoUno.ic:= TCritico;
      marcoUno.t := Milliseconds(300);

      marcoDos.id := 2;
      marcoDos.c := 120;
      marcoDos.prioridad := 2;
      marcoDos.ic:= TCritico;
      marcoDos.t := Milliseconds(400);

      marcoTres.id := 3;
      marcoTres.c := 150;
      marcoTres.prioridad := 1;
      marcoTres.ic:= TCritico;
      marcoTres.t := Milliseconds(500);

      primerHilo := new funcion_hebra(marcoUno'Access);
      segundoHilo := new funcion_hebra(marcoDos'Access);
      tercerHilo := new funcion_hebra(marcoTres'Access);

end Main;
