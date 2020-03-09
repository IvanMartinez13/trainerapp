--
-- PostgreSQL database dump
--

-- Dumped from database version 10.10
-- Dumped by pg_dump version 10.10

SET statement_timeout = 0;
SET lock_timeout = 0;
SET idle_in_transaction_session_timeout = 0;
SET client_encoding = 'UTF8';
SET standard_conforming_strings = on;
SELECT pg_catalog.set_config('search_path', '', false);
SET check_function_bodies = false;
SET xmloption = content;
SET client_min_messages = warning;
SET row_security = off;

--
-- Name: plpgsql; Type: EXTENSION; Schema: -; Owner: 
--

CREATE EXTENSION IF NOT EXISTS plpgsql WITH SCHEMA pg_catalog;


--
-- Name: EXTENSION plpgsql; Type: COMMENT; Schema: -; Owner: 
--

COMMENT ON EXTENSION plpgsql IS 'PL/pgSQL procedural language';


--
-- Name: pgcrypto; Type: EXTENSION; Schema: -; Owner: 
--

CREATE EXTENSION IF NOT EXISTS pgcrypto WITH SCHEMA public;


--
-- Name: EXTENSION pgcrypto; Type: COMMENT; Schema: -; Owner: 
--

COMMENT ON EXTENSION pgcrypto IS 'cryptographic functions';


SET default_tablespace = '';

SET default_with_oids = false;

--
-- Name: ejercicio; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE public.ejercicio (
    id_ejercicio integer NOT NULL,
    objetivo character varying(200) NOT NULL,
    espacio character varying(20) NOT NULL,
    explicacion text NOT NULL,
    reglas text NOT NULL,
    tiempotrabajo integer NOT NULL,
    tiempodescanso integer NOT NULL,
    tiempototal integer NOT NULL,
    id_usuario integer NOT NULL
);


ALTER TABLE public.ejercicio OWNER TO postgres;

--
-- Name: Ejercicio_id_ejercicio_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE public."Ejercicio_id_ejercicio_seq"
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public."Ejercicio_id_ejercicio_seq" OWNER TO postgres;

--
-- Name: Ejercicio_id_ejercicio_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE public."Ejercicio_id_ejercicio_seq" OWNED BY public.ejercicio.id_ejercicio;


--
-- Name: entrenamiento; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE public.entrenamiento (
    id_entrenamiento integer NOT NULL,
    objetivo text NOT NULL,
    numero_jugadores integer NOT NULL,
    material text NOT NULL,
    tiempo_duracion integer NOT NULL,
    id_usuario integer NOT NULL,
    parteinicial integer NOT NULL,
    partefinal integer NOT NULL,
    parteprincipal integer NOT NULL
);


ALTER TABLE public.entrenamiento OWNER TO postgres;

--
-- Name: Entrenamiento_id_entrenamiento_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE public."Entrenamiento_id_entrenamiento_seq"
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public."Entrenamiento_id_entrenamiento_seq" OWNER TO postgres;

--
-- Name: Entrenamiento_id_entrenamiento_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE public."Entrenamiento_id_entrenamiento_seq" OWNED BY public.entrenamiento.id_entrenamiento;


--
-- Name: usuario; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE public.usuario (
    id_usuario integer NOT NULL,
    nombre character varying(20) NOT NULL,
    correo_electronico character varying(200) NOT NULL,
    contrasenya text NOT NULL
);


ALTER TABLE public.usuario OWNER TO postgres;

--
-- Name: Usuario_id_usuario_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE public."Usuario_id_usuario_seq"
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public."Usuario_id_usuario_seq" OWNER TO postgres;

--
-- Name: Usuario_id_usuario_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE public."Usuario_id_usuario_seq" OWNED BY public.usuario.id_usuario;


--
-- Name: entrenamiento_parteinicial_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE public.entrenamiento_parteinicial_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public.entrenamiento_parteinicial_seq OWNER TO postgres;

--
-- Name: entrenamiento_parteinicial_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE public.entrenamiento_parteinicial_seq OWNED BY public.entrenamiento.parteinicial;


--
-- Name: ejercicio id_ejercicio; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.ejercicio ALTER COLUMN id_ejercicio SET DEFAULT nextval('public."Ejercicio_id_ejercicio_seq"'::regclass);


--
-- Name: entrenamiento id_entrenamiento; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.entrenamiento ALTER COLUMN id_entrenamiento SET DEFAULT nextval('public."Entrenamiento_id_entrenamiento_seq"'::regclass);


--
-- Name: usuario id_usuario; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.usuario ALTER COLUMN id_usuario SET DEFAULT nextval('public."Usuario_id_usuario_seq"'::regclass);


--
-- Data for Name: ejercicio; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY public.ejercicio (id_ejercicio, objetivo, espacio, explicacion, reglas, tiempotrabajo, tiempodescanso, tiempototal, id_usuario) FROM stdin;
1	Control y pase	20x20	Los jugadores han de realizar un circuito de pases utilizando el interior del pie.	solo pueden hacer dos toques, el balón ha de ir pegado al pie y han de levantar la cabeza.	20	2	22	2
2	Chut	área	tiros desde la frontal del área	han de tirar a puerta.	15	1	16	2
3	Mejorar forma fisica	medio campo	realizan un circuito de coordinación y fuerza.	realizar el circuito de la forma correcta.	20	4	24	2
\.


--
-- Data for Name: entrenamiento; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY public.entrenamiento (id_entrenamiento, objetivo, numero_jugadores, material, tiempo_duracion, id_usuario, parteinicial, partefinal, parteprincipal) FROM stdin;
1	Mejorar la condicion física y técnica	18	conos, balones, petos y xinos	90	2	3	2	1
\.


--
-- Data for Name: usuario; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY public.usuario (id_usuario, nombre, correo_electronico, contrasenya) FROM stdin;
2	Test	test@email.com	$2a$06$NYLb.wWifidHqWBNpNznMu74rB6BjceugE3AKMlArokV9gb5dmsGG
\.


--
-- Name: Ejercicio_id_ejercicio_seq; Type: SEQUENCE SET; Schema: public; Owner: postgres
--

SELECT pg_catalog.setval('public."Ejercicio_id_ejercicio_seq"', 3, true);


--
-- Name: Entrenamiento_id_entrenamiento_seq; Type: SEQUENCE SET; Schema: public; Owner: postgres
--

SELECT pg_catalog.setval('public."Entrenamiento_id_entrenamiento_seq"', 1, true);


--
-- Name: Usuario_id_usuario_seq; Type: SEQUENCE SET; Schema: public; Owner: postgres
--

SELECT pg_catalog.setval('public."Usuario_id_usuario_seq"', 2, true);


--
-- Name: entrenamiento_parteinicial_seq; Type: SEQUENCE SET; Schema: public; Owner: postgres
--

SELECT pg_catalog.setval('public.entrenamiento_parteinicial_seq', 1, false);


--
-- Name: ejercicio Ejercicio_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.ejercicio
    ADD CONSTRAINT "Ejercicio_pkey" PRIMARY KEY (id_ejercicio);


--
-- Name: usuario Usuario_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.usuario
    ADD CONSTRAINT "Usuario_pkey" PRIMARY KEY (id_usuario);


--
-- Name: entrenamiento pk1_id_entrenamiento; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.entrenamiento
    ADD CONSTRAINT pk1_id_entrenamiento PRIMARY KEY (id_entrenamiento);


--
-- Name: ejercicio Ejercicio_id_usuario_fkey; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.ejercicio
    ADD CONSTRAINT "Ejercicio_id_usuario_fkey" FOREIGN KEY (id_usuario) REFERENCES public.usuario(id_usuario);


--
-- Name: entrenamiento entrenamiento_partefinal_fkey; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.entrenamiento
    ADD CONSTRAINT entrenamiento_partefinal_fkey FOREIGN KEY (partefinal) REFERENCES public.ejercicio(id_ejercicio);


--
-- Name: entrenamiento entrenamiento_parteinicial_fkey; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.entrenamiento
    ADD CONSTRAINT entrenamiento_parteinicial_fkey FOREIGN KEY (parteinicial) REFERENCES public.ejercicio(id_ejercicio);


--
-- Name: entrenamiento entrenamiento_parteprincipal_fkey; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.entrenamiento
    ADD CONSTRAINT entrenamiento_parteprincipal_fkey FOREIGN KEY (parteprincipal) REFERENCES public.ejercicio(id_ejercicio);


--
-- Name: entrenamiento fk2_id_usuario; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.entrenamiento
    ADD CONSTRAINT fk2_id_usuario FOREIGN KEY (id_usuario) REFERENCES public.usuario(id_usuario);


--
-- PostgreSQL database dump complete
--

