library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
--use IEEE.NUMERIC_STD.ALL;

library UNISIM;
use UNISIM.VCOMPONENTS.ALL;

entity dmaloop_top is
    Port (
        -- PS7 fixed ports
        DDR_addr    : inout std_logic_vector(14 downto 0);
        DDR_ba      : inout std_logic_vector(2 downto 0);
        DDR_cas_n   : inout std_logic;
        DDR_ck_n    : inout std_logic;
        DDR_ck_p    : inout std_logic;
        DDR_cke     : inout std_logic;
        DDR_cs_n    : inout std_logic;
        DDR_dm      : inout std_logic_vector(3 downto 0);
        DDR_dq      : inout std_logic_vector(31 downto 0);
        DDR_dqs_n   : inout std_logic_vector(3 downto 0);
        DDR_dqs_p   : inout std_logic_vector(3 downto 0);
        DDR_odt     : inout std_logic;
        DDR_ras_n   : inout std_logic;
        DDR_reset_n : inout std_logic;
        DDR_we_n    : inout std_logic;
        FIXED_IO_ddr_vrn    : inout std_logic;
        FIXED_IO_ddr_vrp    : inout std_logic;
        FIXED_IO_mio        : inout std_logic_vector(53 downto 0);
        FIXED_IO_ps_clk     : inout std_logic;
        FIXED_IO_ps_porb    : inout std_logic;
        FIXED_IO_ps_srstb   : inout std_logic);
end dmaloop_top;

architecture Behavioral of dmaloop_top is

    -- Components
    
    component axis_writer is
        Port (
            clk_i   : in  std_logic;
            rst_i   : in  std_logic;
            data_o  : out STD_LOGIC_VECTOR (31 downto 0);
            keep_o  : out STD_LOGIC_VECTOR (3 downto 0);
            last_o  : out STD_LOGIC;
            ready_i : in  STD_LOGIC;
            valid_o : out STD_LOGIC);
    end component axis_writer;
    
    component ps is
    port (
        -- PS7 fixed ports
        DDR_cas_n   : inout std_logic;
        DDR_cke     : inout std_logic;
        DDR_ck_n    : inout std_logic;
        DDR_ck_p    : inout std_logic;
        DDR_cs_n    : inout std_logic;
        DDR_reset_n : inout std_logic;
        DDR_odt     : inout std_logic;
        DDR_ras_n   : inout std_logic;
        DDR_we_n    : inout std_logic;
        DDR_ba      : inout std_logic_vector(2 downto 0);
        DDR_addr    : inout std_logic_vector(14 downto 0);
        DDR_dm      : inout std_logic_vector(3 downto 0);
        DDR_dq      : inout std_logic_vector(31 downto 0);
        DDR_dqs_n   : inout std_logic_vector(3 downto 0);
        DDR_dqs_p   : inout std_logic_vector(3 downto 0);
        FIXED_IO_mio        : inout std_logic_vector(53 downto 0);
        FIXED_IO_ddr_vrn    : inout std_logic;
        FIXED_IO_ddr_vrp    : inout std_logic;
        FIXED_IO_ps_srstb   : inout std_logic;
        FIXED_IO_ps_clk     : inout std_logic;
        FIXED_IO_ps_porb    : inout std_logic);
    end component ps;
    
begin

    ps_i: component ps
    port map (
        DDR_addr => DDR_addr,
        DDR_ba => DDR_ba,
        DDR_cas_n => DDR_cas_n,
        DDR_ck_n => DDR_ck_n,
        DDR_ck_p => DDR_ck_p,
        DDR_cke => DDR_cke,
        DDR_cs_n => DDR_cs_n,
        DDR_dm => DDR_dm,
        DDR_dq => DDR_dq,
        DDR_dqs_n => DDR_dqs_n,
        DDR_dqs_p => DDR_dqs_p,
        DDR_odt => DDR_odt,
        DDR_ras_n => DDR_ras_n,
        DDR_reset_n => DDR_reset_n,
        DDR_we_n => DDR_we_n,
        FIXED_IO_ddr_vrn => FIXED_IO_ddr_vrn,
        FIXED_IO_ddr_vrp => FIXED_IO_ddr_vrp,
        FIXED_IO_mio => FIXED_IO_mio,
        FIXED_IO_ps_clk => FIXED_IO_ps_clk,
        FIXED_IO_ps_porb => FIXED_IO_ps_porb,
        FIXED_IO_ps_srstb => FIXED_IO_ps_srstb);
    
end Behavioral;
