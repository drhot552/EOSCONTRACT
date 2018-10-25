#include <eosiolib/eosio.hpp>
#include <eosiolib/print.hpp>
using namespace eosio;
using namespace std;
class Brands : public eosio::contract
{
    public:
        using contract::contract;
        /// @abi table
        struct brands
        {
            uint64_t id;
            account_name to;
            account_name from;
            string brands_name;
            string product_name;
            string brands_num;
            string type;
            string reg_dttm;
            string mf_dttm;
            string tx_dttm;
            uint64_t primary_key() const {return id;}
            EOSLIB_SERIALIZE(brands,(id)(to)(from)(brands_name)(product_name)(brands_num)(type)(reg_dttm)(mf_dttm))
        };
        typedef multi_index<N(brands),brands> _brands;
        /// @abi action
        void create(uint64_t id, account_name user, account_name _from, string _brands_name, string _product_name,
                     string _brands_num, string _type, string _reg_dttm, string _mf_dttm, string _tx_dttm)
        {
             _brands tables(_self,_self);

            auto iter=tables.find(id);
            if(iter==tables.end())
            {
                tables.emplace(_self,[&](auto& brands)
                {
                    brands.id = id;
                    brands.to = user;
                    brands.from = _from;
                    brands.brands_num = _brands_num;
                    brands.brands_name = _brands_name;
                    brands.product_name = _product_name;
                    brands.type = _type;
                    brands.reg_dttm = _reg_dttm;
                    brands.mf_dttm = _mf_dttm;
                    brands.tx_dttm = _tx_dttm;
                });
            }
            else
            {
                uint64_t getuser;
                getuser=iter->to;
            }
        }
        //delete
        void del(uint64_t id, string _brands_num)
        {
            _brands tables(_self,_self);
            auto iter=tables.find(id);
            if(iter!=tables.end())
            {
                tables.erase(iter);
            }
        }
        //edit (product edit)
        void edit(uint64_t id, string _product_name, string _brands_num, string _type, string _reg_dttm, string _mf_dttm)
        {
             _brands tables(_self,_self);
            auto iter=tables.find(id);
            if(iter!=tables.end())
            {
                tables.modify(iter,_self,[&](auto& edit_table)
                {
                  edit_table.brands_num = _brands_num;
                  edit_table.product_name = _product_name;
                  edit_table.reg_dttm = _reg_dttm;
                  edit_table.mf_dttm = _mf_dttm;
                  edit_table.type = _type;

                });
            }
        }
        void auth(uint64_t id, account_name _to, account_name _from, string _tx_dttm)
        {
            _brands tables(_self,_self);
           auto iter=tables.find(id);
           if(iter!=tables.end())
           {
               tables.modify(iter,_self,[&](auto& edit_table)
               {
                 edit_table.to = _to;
                 edit_table.from = _from;
                 edit_table.tx_dttm = _tx_dttm;
               });
           }
        }
};
EOSIO_ABI(Brands,(create)(del)(edit)(auth))
