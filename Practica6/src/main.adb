with controlador; use controlador;
with GNAT.IO;  use GNAT.IO;
with Ada.Real_Time; use Ada.Real_Time;
with Ada.Calendar; use Ada.Calendar;
procedure Main is

   varContador: aliased Integer;
   type contador is access all Integer;

   task type mostrarHora(valContador: contador);
   task body mostrarHora is
         tiempoActal : Ada.Calendar.Time;
         intUno : Time_Span;
         intDos : Time_Span;
         s_d : Day_Duration;
         h : Integer;
         m : Integer;
      s : Integer;
      dia : Day_Number;
      mes : Month_Number;
      year_a : Year_Number;
      n : Ada.Real_Time.Time;
      int : Time_Span;
   begin
      while valContador.all < 10 loop
         intUno := Milliseconds(3600);
         intDos := Milliseconds(60);
         tiempoActal := Clock;
         s_d := Seconds(tiempoActal);
         h := integer(s_d) / 3600;
         m := (integer(s_d) mod 3600) / 60;
         s := integer(s_d) mod 60;
         dia := Day(tiempoActal);
         mes := Month(tiempoActal);
         year_a := Year(tiempoActal);
         Put_Line  ("Tiempo con reloj calendario dia/mes/anio ---- hora:minutos:segundos");
         Put(integer'Image(dia));
         Put("/");
         Put(integer'Image(mes));
         Put("/");
         Put(integer'Image(year_a));
         Put("----");
         Put(integer'Image(h));
         Put(":");
         Put(integer'Image(m));
         Put(":");
         Put_Line(integer'Image(s));
         int := Milliseconds(5000);
               n := Clock;
               n:= n + int;
            delay until n;
     end loop;
   end;

   task type contarControlC(valContador: contador);
   task body contarControlC is
   begin
      while valContador.all < 10  loop

         select
            ObjetoControlador.wait;
            valContador.all := valContador.all + 1;
         or

               delay 6.0;
               Put_Line  ("6 Segundos sin presionar ctrl+c");

         end select;
      end loop;

   end;

   task type mostrarControlC(valContador: contador);
   task body mostrarControlC is
       n : Ada.Real_Time.Time;
               int : Time_Span;

   begin
         while valContador.all < 10 loop
               int := Milliseconds(2000);
               n := Clock;
               n:= n + int;
            delay until n;
         Put  ("El ctrl+c ha sido pulsado: ");
         Put(integer'Image(valContador.all));
         Put_Line(" veces");
      end loop;
   end;

   tareaHora : mostrarHora(varContador'Access);
   tareaContar : contarControlC(varContador'Access);
   tareaMostrar : mostrarControlC(varContador'Access);

begin
   --  Insert code here.
   null;
end Main;
